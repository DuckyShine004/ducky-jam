#include "game/gameplay/effects/note_effect.hpp"

namespace game::gameplay::effects {

NoteEffect::NoteEffect(int shader_id) : Effect(shader_id) {
}

void NoteEffect::apply_shader_parameters(engine::graphic::shader::Shader &) const {
}

} // namespace game::gameplay::effects
