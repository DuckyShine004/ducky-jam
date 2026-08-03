#include "game/gameplay/effects/lighting_effect.hpp"

using namespace engine::graphics::blending;
using namespace engine::graphics::blending::enums;

namespace game::gameplay::effects {

LightingEffect::LightingEffect(int shader_id)
    : Effect(shader_id, BlendParameters{
                            .equation = BlendEquation::Add,
                            .source = BlendMode::SourceAlpha,
                            .destination = BlendMode::One,
                        }) {
}

void LightingEffect::apply_shader_parameters(engine::graphics::shader::Shader &shader) const {
    shader.set_float("u_bloom_intensity", 0.0f);
}

} // namespace game::gameplay::effects
