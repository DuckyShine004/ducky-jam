#pragma once

#include "engine/graphic/effect/effect.hpp"

namespace game::gameplay::effects {

class LightingEffect final : public engine::graphic::effect::Effect {
  public:
    LightingEffect(int shader_id);

  private:
    void apply_shader_parameters(engine::graphic::shader::Shader &shader) const override;
};

} // namespace game::gameplay::effects
