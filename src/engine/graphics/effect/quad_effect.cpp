#include <stdexcept>

#include "engine/graphics/effect/quad_effect.hpp"

using namespace core::structs;

using namespace engine::graphics::blending;
using namespace engine::graphics::blending::enums;
using namespace engine::graphics::shader;

namespace engine::graphics::effect {

QuadEffect::QuadEffect(int shader_id,
                       Vector2<float> draw_size,
                       Vector2<float> shape_size,
                       Vector4<float> corner_radius,
                       Vector2<float> shadow_offset,
                       float shadow_blur,
                       Vector4<std::uint8_t> shadow_colour,
                       float bloom_intensity)
    : Effect(shader_id,
             BlendParameters{
                 .equation = BlendEquation::Add,
                 .source = BlendMode::SourceAlpha,
                 .destination = BlendMode::OneMinusSourceAlpha,
             }),
      m_draw_size(draw_size), m_shape_size(shape_size), m_shadow_offset(shadow_offset),
      m_corner_radius(corner_radius.x, corner_radius.y, corner_radius.z, corner_radius.w),
      m_shadow_colour(static_cast<float>(shadow_colour.r) / 255.0f,
                      static_cast<float>(shadow_colour.g) / 255.0f,
                      static_cast<float>(shadow_colour.b) / 255.0f,
                      static_cast<float>(shadow_colour.a) / 255.0f),
      m_shadow_blur(shadow_blur), m_bloom_intensity(bloom_intensity) {
    if (draw_size.w <= 0.0f || draw_size.h <= 0.0f || shape_size.w < 0.0f || shape_size.h < 0.0f) {
        throw std::invalid_argument("Quad dimensions must be non-negative and its draw dimensions must be positive");
    }

    if (shadow_blur < 0.0f) {
        throw std::invalid_argument("Shadow blur cannot be negative");
    }

    if (bloom_intensity < 0.0f) {
        throw std::invalid_argument("Bloom intensity cannot be negative");
    }
}

void QuadEffect::apply_shader_parameters(Shader &shader) const {
    shader.set_vector2f("u_draw_size", m_draw_size);
    shader.set_vector2f("u_shape_size", m_shape_size);
    shader.set_vector4f("u_corner_radius", m_corner_radius);
    shader.set_vector2f("u_shadow_offset", m_shadow_offset);
    shader.set_float("u_shadow_blur", m_shadow_blur);
    shader.set_vector4f("u_shadow_colour", m_shadow_colour);
    shader.set_float("u_bloom_intensity", m_bloom_intensity);
}

} // namespace engine::graphics::effect
