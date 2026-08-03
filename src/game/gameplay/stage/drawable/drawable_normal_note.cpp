#include "game/gameplay/stage/drawable/drawable_normal_note.hpp"

using namespace engine::graphics::renderer;
using namespace engine::graphics::drawable;

namespace game::gameplay::stage::drawable {

DrawableNormalNote::DrawableNormalNote(const Note &note, const Sprite &head) : DrawableNote(note, head) {
}

} // namespace game::gameplay::stage::drawable
