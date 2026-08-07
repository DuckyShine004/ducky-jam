#include "game/gameplay/effects/lighting_effect.hpp"

namespace game::gameplay::effects {

namespace graphics = engine::graphics;

LightingEffect::LightingEffect(int shader_id)
    : Effect(shader_id, graphics::blending::BlendParameters{
                            .equation = graphics::blending::enums::BlendEquation::Add,
                            .source = graphics::blending::enums::BlendMode::SourceAlpha,
                            .destination = graphics::blending::enums::BlendMode::One,
                        }) {
}

void LightingEffect::apply_shader_parameters(graphics::shader::Shader &shader) const {
    shader.set_float("u_bloom_intensity", 0.0f);
}

} // namespace game::gameplay::effects
