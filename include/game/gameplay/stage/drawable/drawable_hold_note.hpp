#pragma once

#include "engine/graphic/drawable/sprite.hpp"

#include "game/gameplay/stage/drawable/drawable_note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableHoldNote final : public DrawableNote {
  public:
    DrawableHoldNote(const Note &note, const engine::graphic::drawable::Sprite &head, const engine::graphic::drawable::Sprite &body, const engine::graphic::drawable::Sprite &tail);

    // offset y = y - approach_rate*current_time
    void update(double track_time) override;
    void submit(engine::graphic::render::Renderer &renderer) const override;

  private:
    engine::graphic::drawable::Sprite m_body;
    engine::graphic::drawable::Sprite m_tail;
};

} // namespace game::gameplay::stage::drawable
