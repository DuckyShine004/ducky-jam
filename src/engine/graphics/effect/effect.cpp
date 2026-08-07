#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

Effect::Effect(int shader_id, blending::BlendParameters blend_parameters) : m_shader_id(shader_id), m_blend_parameters(blend_parameters) {
}

void Effect::apply(shader::Shader &shader) const {
    m_blend_parameters.apply();
    apply_shader_parameters(shader);
}

const blending::BlendParameters &Effect::blend_parameters() const {
    return m_blend_parameters;
}

int Effect::shader_id() const {
    return m_shader_id;
}

} // namespace engine::graphics::effect
