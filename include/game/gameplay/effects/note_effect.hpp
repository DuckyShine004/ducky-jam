#pragma once

#include "engine/graphic/effect/effect.hpp"

namespace game::gameplay::effects {

class NoteEffect final : public engine::graphic::effect::Effect {
  public:
    NoteEffect(int shader_id);

    void apply() const override;
};

} // namespace game::gameplay::effects
