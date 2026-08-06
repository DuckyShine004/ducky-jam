#include <stdexcept>

#include "engine/graphics/effect/bloom_effect.hpp"

using namespace engine::graphics::blending;
using namespace engine::graphics::blending::enums;
using namespace engine::graphics::shader;

namespace engine::graphics::effect {

BloomEffect::BloomEffect(int shader_id, float intensity)
    : Effect(shader_id,
             BlendParameters{
                 .equation = BlendEquation::Add,
                 .source = BlendMode::SourceAlpha,
                 .destination = BlendMode::OneMinusSourceAlpha,
             }),
      m_intensity(intensity) {
    if (intensity < 0.0f) {
        throw std::invalid_argument("Bloom intensity cannot be negative");
    }
}

void BloomEffect::apply_shader_parameters(Shader &shader) const {
    shader.set_float("u_bloom_intensity", m_intensity);
}

float BloomEffect::intensity() const {
    return m_intensity;
}

} // namespace engine::graphics::effect
