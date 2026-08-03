#pragma once

#include "engine/graphics/effect/effect.hpp"

namespace game::gameplay::effects {

class LightingEffect final : public engine::graphics::effect::Effect {
  public:
    LightingEffect(int shader_id);

  private:
    void apply_shader_parameters(engine::graphics::shader::Shader &shader) const override;
};

} // namespace game::gameplay::effects
