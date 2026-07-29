#include "game/gameplay/effects/lighting_effect.hpp"

using namespace engine::graphic::blending;
using namespace engine::graphic::blending::enums;

namespace game::gameplay::effects {

LightingEffect::LightingEffect(int shader_id)
    : Effect(shader_id, BlendParameters{
                            .equation = BlendEquation::Add,
                            .source = BlendMode::SourceAlpha,
                            .destination = BlendMode::One,
                        }) {
}

void LightingEffect::apply_shader_parameters(engine::graphic::shader::Shader &) const {
}

} // namespace game::gameplay::effects
