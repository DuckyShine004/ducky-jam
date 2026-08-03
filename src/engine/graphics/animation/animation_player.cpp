#include "engine/graphics/animation/animation_player.hpp"

using namespace engine::graphics::drawable;

namespace engine::graphics::animation {

AnimationPlayer::AnimationPlayer(double frame_rate) : m_frame_rate(frame_rate), m_elapsed_time(0.0), m_frame_index(0), m_playing(false) {
}

void AnimationPlayer::add_frame(const Sprite &sprite) {
    m_frames.emplace_back(sprite);
}

void AnimationPlayer::play() {
    m_elapsed_time = 0.0;
    m_frame_index = 0;
    m_playing = !m_frames.empty() && m_frame_rate > 0.0;
}

void AnimationPlayer::update(double delta_time) {
    if (!m_playing || delta_time <= 0.0) {
        return;
    }

    m_elapsed_time += delta_time;

    const std::size_t elapsed_frames = static_cast<std::size_t>(m_elapsed_time * m_frame_rate);

    m_frame_index = elapsed_frames % m_frames.size();
}

void AnimationPlayer::submit(engine::graphics::renderer::Renderer &renderer) const {
    if (m_playing) {
        m_frames[m_frame_index].submit(renderer);
    }
}

bool AnimationPlayer::playing() const {
    return m_playing;
}

} // namespace engine::graphics::animation
