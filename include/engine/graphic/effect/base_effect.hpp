#pragma once

#include "engine/graphic/effect/effect.hpp"

namespace engine::graphic::effect {

class BaseEffect final : public Effect {
  public:
    BaseEffect(int shader_id);

    void apply() const override;
};

} // namespace engine::graphic::effect
