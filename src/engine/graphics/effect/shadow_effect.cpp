#include "engine/graphics/effect/shadow_effect.hpp"

namespace engine::graphics::effect {

ShadowEffect::ShadowEffect(int shader_id, core::structs::Vector2<float> shadow_size, float blur_radius, float corner_radius) : Effect(shader_id, blending::BlendParameters{}), m_shadow_size(shadow_size), m_blur_radius(blur_radius), m_corner_radius(corner_radius) {
}

void ShadowEffect::apply_shader_parameters(shader::Shader &shader) const {
    shader.set_vector2f("u_shadow_size", m_shadow_size);
    shader.set_float("u_blur_radius", m_blur_radius);
    shader.set_float("u_corner_radius", m_corner_radius);
}

} // namespace engine::graphics::effect
