#include "engine/graphic/effect/base_effect.hpp"

using namespace engine::graphic::shader;

using namespace engine::graphic::blending;
using namespace engine::graphic::blending::enums;

namespace engine::graphic::effect {

BaseEffect::BaseEffect(int shader_id)
    : Effect(shader_id, BlendParameters{
                            .equation = BlendEquation::Add,
                            .source = BlendMode::SourceAlpha,
                            .destination = BlendMode::OneMinusSourceAlpha,
                        }) {
}

void BaseEffect::apply_shader_parameters(Shader &shader) const {
}

} // namespace engine::graphic::effect
