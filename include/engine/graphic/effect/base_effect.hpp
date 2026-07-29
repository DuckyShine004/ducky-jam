#pragma once

#include "engine/graphic/effect/effect.hpp"

namespace engine::graphic::effect {

class BaseEffect final : public Effect {
  public:
    BaseEffect(int shader_id);

  private:
    void apply_shader_parameters(engine::graphic::shader::Shader &shader) const override;
};

} // namespace engine::graphic::effect
