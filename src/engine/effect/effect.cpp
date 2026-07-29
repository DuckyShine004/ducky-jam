#include "engine/graphic/shader/shader_manager.hpp"

#include "engine/graphic/effect/effect.hpp"

using namespace engine::graphic::blending;
using namespace engine::graphic::shader;

namespace engine::graphic::effect {

Effect::Effect(int shader_id, BlendParameters blend_parameters) : m_shader_id(shader_id), m_blend_parameters(blend_parameters) {
}

void Effect::apply() const {
    ShaderManager::get_instance().use_shader(m_shader_id);

    m_blend_parameters.apply();

    Shader &shader = ShaderManager::get_instance().get_active_shader();

    apply_shader_parameters(shader);
}

const BlendParameters &Effect::blend_parameters() const {
    return m_blend_parameters;
}

int Effect::shader_id() const {
    return m_shader_id;
}

} // namespace engine::graphic::effect
