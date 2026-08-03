#pragma once

#include "engine/graphics/drawable/sprite.hpp"

#include "game/gameplay/stage/drawable/drawable_note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableHoldNote final : public DrawableNote {
  public:
    DrawableHoldNote(const Note &note, const engine::graphics::drawable::Sprite &head, const engine::graphics::drawable::Sprite &body, const engine::graphics::drawable::Sprite &tail);

    // offset y = y - approach_rate*current_time
    void update(double track_time) override;
    void submit(engine::graphics::renderer::Renderer &renderer) const override;

  private:
    engine::graphics::drawable::Sprite m_body;
    engine::graphics::drawable::Sprite m_tail;
};

} // namespace game::gameplay::stage::drawable
