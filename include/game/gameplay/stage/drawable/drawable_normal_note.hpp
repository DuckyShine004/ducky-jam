#pragma once

#include "engine/graphics/drawable/sprite.hpp"

#include "game/gameplay/stage/drawable/drawable_note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableNormalNote final : public DrawableNote {
  public:
    DrawableNormalNote(const Note &note, const engine::graphics::drawable::Sprite &head);
};

} // namespace game::gameplay::stage::drawable
