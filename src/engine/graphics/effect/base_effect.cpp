#include "engine/graphics/effect/base_effect.hpp"

namespace engine::graphics::effect {

BaseEffect::BaseEffect(int shader_id)
    : Effect(shader_id, blending::BlendParameters{
                            .equation = blending::enums::BlendEquation::Add,
                            .source = blending::enums::BlendMode::SourceAlpha,
                            .destination = blending::enums::BlendMode::OneMinusSourceAlpha,
                        }) {
}

void BaseEffect::apply_shader_parameters(shader::Shader &shader) const {
    shader.set_float("u_bloom_intensity", 0.0f);
}

} // namespace engine::graphics::effect
