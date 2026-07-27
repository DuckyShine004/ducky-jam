#pragma once

#include "engine/graphic/effect/effect.hpp"

namespace game::gameplay::effects {

class LightingEffect final : public engine::graphic::effect::Effect {
  public:
    LightingEffect(int shader_id);

    void apply() const override;
};

} // namespace game::gameplay::effects
