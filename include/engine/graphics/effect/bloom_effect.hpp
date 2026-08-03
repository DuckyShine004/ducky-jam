#pragma once

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

class BloomEffect final : public Effect {
  public:
    BloomEffect(int shader_id, float intensity);

    float intensity() const;

  private:
    void apply_shader_parameters(engine::graphics::shader::Shader &shader) const override;

    float m_intensity;
};

} // namespace engine::graphics::effect
