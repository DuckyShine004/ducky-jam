#pragma once

#include <cstddef>
#include <vector>

#include "engine/graphic/drawable/sprite.hpp"

namespace engine::graphic::animation {

class AnimationPlayer {
  public:
    AnimationPlayer(double frame_rate);

    void add_frame(const engine::graphic::drawable::Sprite &sprite);

    void play();
    void update(double delta_time);
    void submit(engine::graphic::render::Renderer &renderer) const;

    bool playing() const;

  private:
    double m_frame_rate;
    double m_elapsed_time;

    std::vector<engine::graphic::drawable::Sprite> m_frames;
    std::size_t m_frame_index;

    bool m_playing;
    bool m_looping;
};

} // namespace engine::graphic::animation
