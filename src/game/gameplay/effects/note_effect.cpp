#include "game/gameplay/effects/note_effect.hpp"

namespace game::gameplay::effects {

NoteEffect::NoteEffect(int shader_id) : Effect(shader_id) {
}

void NoteEffect::apply_shader_parameters(engine::graphics::shader::Shader &shader) const {
    shader.set_float("u_bloom_intensity", 0.0f);
}

} // namespace game::gameplay::effects
