#include "engine/graphic/shader/shader_manager.hpp"

#include "game/gameplay/effects/lighting_effect.hpp"

using namespace engine::graphic::shader;

namespace game::gameplay::effects {

LightingEffect::LightingEffect(int shader_id) : Effect(shader_id) {
}

void LightingEffect::apply() const {
    ShaderManager::get_instance().use_shader(m_shader_id);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}

} // namespace game::gameplay::effects
