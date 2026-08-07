#include "game/gameplay/stage/drawable/drawable_normal_note.hpp"

namespace game::gameplay::stage::drawable {

namespace graphics = engine::graphics;

DrawableNormalNote::DrawableNormalNote(const Note &note, const graphics::drawable::Sprite &head) : DrawableNote(note, head) {
}

} // namespace game::gameplay::stage::drawable
