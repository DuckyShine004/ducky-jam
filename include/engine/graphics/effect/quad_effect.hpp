#pragma once

#include <cstdint>

#include <glm/glm.hpp>

#include "core/structs/vector2.hpp"
#include "core/structs/vector4.hpp"

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

class QuadEffect final : public Effect {
  public:
    QuadEffect(int shader_id,
               core::structs::Vector2<float> draw_size,
               core::structs::Vector2<float> shape_size,
               core::structs::Vector4<float> corner_radius,
               core::structs::Vector2<float> shadow_offset,
               float shadow_blur,
               core::structs::Vector4<std::uint8_t> shadow_colour,
               float bloom_intensity);

  private:
    void apply_shader_parameters(engine::graphics::shader::Shader &shader) const override;

    core::structs::Vector2<float> m_draw_size;
    core::structs::Vector2<float> m_shape_size;
    core::structs::Vector2<float> m_shadow_offset;

    glm::vec4 m_corner_radius;
    glm::vec4 m_shadow_colour;

    float m_shadow_blur;
    float m_bloom_intensity;
};

} // namespace engine::graphics::effect
