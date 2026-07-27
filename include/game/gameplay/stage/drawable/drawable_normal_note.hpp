#pragma once

#include "engine/graphic/drawable/sprite.hpp"

#include "game/gameplay/stage/drawable/drawable_note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableNormalNote final : public DrawableNote {
  public:
    DrawableNormalNote(const Note &note, const engine::graphic::drawable::Sprite &head);
};

} // namespace game::gameplay::stage::drawable
