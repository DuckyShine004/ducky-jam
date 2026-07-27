#include "engine/graphic/shader/shader_manager.hpp"

#include "game/gameplay/effects/note_effect.hpp"

using namespace engine::graphic::shader;

namespace game::gameplay::effects {

NoteEffect::NoteEffect(int shader_id) : Effect(shader_id) {
}

void NoteEffect::apply() const {
    ShaderManager::get_instance().use_shader(m_shader_id);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

} // namespace game::gameplay::effects
