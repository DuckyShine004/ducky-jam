#include "game/gameplay/stage/drawable/drawable_normal_note.hpp"

using namespace engine::graphic::render;
using namespace engine::graphic::drawable;

namespace game::gameplay::stage::drawable {

DrawableNormalNote::DrawableNormalNote(const Note &note, const Sprite &head) : DrawableNote(note, head) {
}

} // namespace game::gameplay::stage::drawable
