#pragma once

#include <memory>

#include "engine/graphic/animation/animation_player.hpp"

#include "game/gameplay/stage/drawable/drawable_note.hpp"

namespace game::gameplay::stage {

class Lane {
  public:
    Lane(int lighting_frame_rate);

    void update(double track_time, double delta_time);
    void add_note(std::unique_ptr<drawable::DrawableNote> note);

    const std::vector<drawable::DrawableNote *> &active_notes() const;

    engine::graphic::animation::AnimationPlayer &lighting_hold();
    engine::graphic::animation::AnimationPlayer &lighting_normal();

  private:
    std::vector<std::unique_ptr<drawable::DrawableNote>> m_notes;
    std::vector<drawable::DrawableNote *> m_active_notes;

    engine::graphic::animation::AnimationPlayer m_lighting_hold;
    engine::graphic::animation::AnimationPlayer m_lighting_normal;

    int m_note_offset;
};

} // namespace game::gameplay::stage
