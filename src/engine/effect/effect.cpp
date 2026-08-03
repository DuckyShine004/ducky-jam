#include "engine/graphics/shader/shader_manager.hpp"

#include "engine/graphics/effect/effect.hpp"

using namespace engine::graphics::blending;
using namespace engine::graphics::shader;

namespace engine::graphics::effect {

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

} // namespace engine::graphics::effect
