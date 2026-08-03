#pragma once

#include <cstddef>
#include <vector>

#include "engine/graphics/drawable/sprite.hpp"

namespace engine::graphics::animation {

class AnimationPlayer {
  public:
    AnimationPlayer(double frame_rate);

    void add_frame(const engine::graphics::drawable::Sprite &sprite);

    void play();
    void update(double delta_time);
    void submit(engine::graphics::renderer::Renderer &renderer) const;

    bool playing() const;

  private:
    double m_frame_rate;
    double m_elapsed_time;

    std::vector<engine::graphics::drawable::Sprite> m_frames;
    std::size_t m_frame_index;

    bool m_playing;
    bool m_looping;
};

} // namespace engine::graphics::animation
