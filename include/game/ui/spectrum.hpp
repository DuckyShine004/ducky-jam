#pragma once

#include "engine/audio/audio_buffer.hpp"
#include "engine/audio/fft/fft.hpp"
#include "engine/ui/ui_node.hpp"

namespace game::ui {

class Spectrum final : public engine::ui::UiNode {
  public:
    Spectrum(const engine::ui::components::Layout &layout, int bars, float gap);

    void update(double delta_time) override;
    void update_by_audio(engine::audio::AudioBuffer &audio_buffer, double track_time) override;

    void submit(engine::graphics::renderer::Renderer &renderer) const override;

  private:
    static inline constexpr float default_attack_speed = 0.025f;
    static inline constexpr float default_release_speed = 0.18f;

    static inline constexpr float minimum_frequency = 50.0f;
    static inline constexpr float maximum_frequency = 20000.0f;

    static inline constexpr float minimum_decibels = -70.0f;
    static inline constexpr float maximum_decibels = 0.0f;

    int m_bars;
    float m_gap;

    engine::audio::fft::FFT m_fft;

    std::vector<float> m_target_levels;
    std::vector<float> m_displayed_levels;
};

} // namespace game::ui
