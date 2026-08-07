#include "engine/graphics/effect/quad_effect.hpp"

#include "core/exceptions/invalid_argument_exception.hpp"

namespace engine::graphics::effect {

namespace exceptions = core::exceptions;

QuadEffect::QuadEffect(int shader_id, core::structs::Vector2<float> draw_size, core::structs::Vector2<float> shape_size, core::structs::Vector4<float> corner_radius, core::structs::Vector2<float> shadow_offset, float shadow_blur, core::structs::Vector4<std::uint8_t> shadow_colour,
                       float bloom_intensity)
    : Effect(shader_id,
             blending::BlendParameters{
                 .equation = blending::enums::BlendEquation::Add,
                 .source = blending::enums::BlendMode::SourceAlpha,
                 .destination = blending::enums::BlendMode::OneMinusSourceAlpha,
             }),
      m_draw_size(draw_size), m_shape_size(shape_size), m_shadow_offset(shadow_offset), m_corner_radius(corner_radius.x, corner_radius.y, corner_radius.z, corner_radius.w),
      m_shadow_colour(static_cast<float>(shadow_colour.r) / 255.0f, static_cast<float>(shadow_colour.g) / 255.0f, static_cast<float>(shadow_colour.b) / 255.0f, static_cast<float>(shadow_colour.a) / 255.0f), m_shadow_blur(shadow_blur), m_bloom_intensity(bloom_intensity) {
    if (draw_size.w <= 0.0f || draw_size.h <= 0.0f || shape_size.w < 0.0f || shape_size.h < 0.0f) {
        throw exceptions::InvalidArgumentException("Quad dimensions must be non-negative and its draw dimensions must be positive");
    }

    if (shadow_blur < 0.0f) {
        throw exceptions::InvalidArgumentException("Shadow blur cannot be negative");
    }

    if (bloom_intensity < 0.0f) {
        throw exceptions::InvalidArgumentException("Bloom intensity cannot be negative");
    }
}

void QuadEffect::apply_shader_parameters(shader::Shader &shader) const {
    shader.set_vector2f("u_draw_size", m_draw_size);
    shader.set_vector2f("u_shape_size", m_shape_size);
    shader.set_vector4f("u_corner_radius", m_corner_radius);
    shader.set_vector2f("u_shadow_offset", m_shadow_offset);
    shader.set_float("u_shadow_blur", m_shadow_blur);
    shader.set_vector4f("u_shadow_colour", m_shadow_colour);
    shader.set_float("u_bloom_intensity", m_bloom_intensity);
}

} // namespace engine::graphics::effect
