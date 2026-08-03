#pragma once

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

class BaseEffect final : public Effect {
  public:
    BaseEffect(int shader_id);

  private:
    void apply_shader_parameters(engine::graphics::shader::Shader &shader) const override;
};

} // namespace engine::graphics::effect
