#pragma once

#include "core/structs/vector2.hpp"

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

class ShadowEffect final : public Effect {
  public:
    ShadowEffect(int shader_id, core::structs::Vector2<float> shadow_size, float blur_radius, float corner_radius);

  private:
    void apply_shader_parameters(engine::graphics::shader::Shader &shader) const override;

    core::structs::Vector2<float> m_shadow_size;

    float m_blur_radius;
    float m_corner_radius;
};

} // namespace engine::graphics::effect
