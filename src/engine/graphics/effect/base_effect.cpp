#include "engine/graphics/effect/base_effect.hpp"

using namespace engine::graphics::shader;

using namespace engine::graphics::blending;
using namespace engine::graphics::blending::enums;

namespace engine::graphics::effect {

BaseEffect::BaseEffect(int shader_id)
    : Effect(shader_id, BlendParameters{
                            .equation = BlendEquation::Add,
                            .source = BlendMode::SourceAlpha,
                            .destination = BlendMode::OneMinusSourceAlpha,
                        }) {
}

void BaseEffect::apply_shader_parameters(Shader &shader) const {
    shader.set_float("u_bloom_intensity", 0.0f);
}

} // namespace engine::graphics::effect
