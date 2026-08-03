#include <algorithm>

#include "engine/graphics/model/quad.hpp"
#include "engine/graphics/effect/effect_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include "game/ui/spectrum.hpp"

using namespace engine::audio;

using namespace engine::ui::components;

using namespace engine::graphics::model;
using namespace engine::graphics::effect;
using namespace engine::graphics::renderer;
using namespace engine::graphics::texture;

namespace game::ui {

Spectrum::Spectrum(const Layout &layout, int bars, float gap) : UiNode(layout), m_bars(bars), m_gap(gap), m_target_levels(bars, 0.0f), m_displayed_levels(bars, 0.0f) {
}

void Spectrum::update(double delta_time) {
    for (std::size_t i = 0; i < m_bars; ++i) {
        const float target = m_target_levels[i];

        const float duration = target > m_displayed_levels[i] ? m_ATTACK_SPEED : m_RELEASE_SPEED;
        const float factor = 1.0f - std::exp(-static_cast<float>(delta_time) / duration);

        m_displayed_levels[i] += (target - m_displayed_levels[i]) * factor;
    }
}

void Spectrum::update_by_audio(AudioBuffer &audio_buffer, double track_time) {
    const int N = m_fft.resolution();
    const int N_HALF = N >> 1;

    const std::int64_t current_frame = static_cast<std::int64_t>(track_time * static_cast<double>(audio_buffer.samplerate()) / 1000.0f);
    const std::int64_t first_frame = current_frame - static_cast<std::int64_t>(N);

    const int channels = audio_buffer.channels();

    std::vector<std::complex<float>> input(N);

    for (std::size_t i = 0; i < N; ++i) {
        const std::int64_t frame = first_frame + static_cast<std::int64_t>(i);

        float sample = 0.0f;

        if (frame >= 0 && frame < static_cast<std::int64_t>(audio_buffer.frames())) {
            for (int channel = 0; channel < channels; ++channel) {
                const std::size_t sample_index = static_cast<std::size_t>(frame) * static_cast<std::size_t>(channels) + static_cast<std::size_t>(channel);

                sample += audio_buffer.samples(sample_index);
            }

            sample /= static_cast<float>(channels);
        }

        input[i] = {sample * m_fft.hann_window(i), 0.0f};
    }

    const std::vector<std::complex<float>> output = std::move(m_fft.update(input));

    /* FIX: Need an actual audio engineer to help me verify this is correct, also tweak settings later */
    const float nyquist = static_cast<float>(audio_buffer.samplerate()) * 0.5f;
    const float highest_frequency = std::min(m_MAXIMUM_FREQUENCY, nyquist);
    const float frequency_per_bin = static_cast<float>(audio_buffer.samplerate()) / static_cast<float>(N);

    // Hann reduces amplitude, so compensate for its gain.
    const float magnitude_scale = 2.0f / m_fft.hann_window_total();
    const float frequency_ratio = highest_frequency / m_MINIMUM_FREQUENCY;

    for (int bar = 0; bar < m_bars; ++bar) {
        const float start_t = static_cast<float>(bar) / static_cast<float>(m_bars);
        const float end_t = static_cast<float>(bar + 1) / static_cast<float>(m_bars);

        const float lower_frequency = m_MINIMUM_FREQUENCY * std::pow(frequency_ratio, start_t);
        const float upper_frequency = m_MINIMUM_FREQUENCY * std::pow(frequency_ratio, end_t);

        const int first_bin = std::clamp(static_cast<int>(std::floor(lower_frequency / frequency_per_bin)), 1, N / 2);
        const int last_bin = std::clamp(static_cast<int>(std::ceil(upper_frequency / frequency_per_bin)), first_bin, N / 2);

        float peak_magnitude = 0.0f;

        for (int bin = first_bin; bin <= last_bin; ++bin) {
            const float magnitude = std::abs(output[bin]) * magnitude_scale;
            peak_magnitude = std::max(peak_magnitude, magnitude);
        }

        const float decibels = 20.0f * std::log10(std::max(peak_magnitude, 1.0e-8f));

        m_target_levels[bar] = std::clamp((decibels - m_MINIMUM_DECIBELS) / (m_MAXIMUM_DECIBELS - m_MINIMUM_DECIBELS), 0.0f, 1.0f);
    }
}

void Spectrum::submit(Renderer &renderer) const {
    const float content_x = m_bound.x + m_layout.padding.left;
    const float content_y = m_bound.y + m_layout.padding.top;
    const float content_width = m_bound.width - m_layout.padding.left - m_layout.padding.right;
    const float content_height = m_bound.height - m_layout.padding.top - m_layout.padding.bottom;
    const float total_gap = m_gap * static_cast<float>(m_bars - 1);

    if (content_width <= total_gap || content_height <= 0.0f) {
        return;
    }

    const float bar_width = (content_width - total_gap) / static_cast<float>(m_bars);

    // UI uses top-left coordinates, renderer uses bottom-left.
    const float baseline = 1440.0f - content_y - content_height;

    auto &textures = TextureManager::get_instance();

    const std::string texture_path = "resources/core/textures/colours/white.png";

    const int texture_id = textures.get_texture_id(texture_path);

    const Region &region = textures.get_texture(texture_path).get_region(texture_path);

    const float u = (region.uv.u0 + region.uv.u1) * 0.5f;
    const float v = (region.uv.v0 + region.uv.v1) * 0.5f;

    const EffectPtr effect = EffectManager::get_instance().get_bloom_effect(m_layout.bloom.intensity);

    for (std::size_t i = 0; i < m_bars; ++i) {
        const float level = std::clamp(m_displayed_levels[i], 0.0f, 1.0f);

        const float bar_height = level * content_height;

        if (bar_height <= 0.0f) {
            continue;
        }

        renderer.queue(Quad{
            .x = content_x + static_cast<float>(i) * (bar_width + m_gap),
            .y = baseline,
            .width = bar_width,
            .height = bar_height,
            .texture_id = texture_id,
            .effect = effect,
            .colour = m_layout.colour,
            .uv =
                {
                    .u0 = u,
                    .u1 = u,
                    .v0 = v,
                    .v1 = v,
                },
        });
    }
}

} // namespace game::ui
