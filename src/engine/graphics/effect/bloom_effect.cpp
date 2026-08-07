#include "engine/graphics/effect/bloom_effect.hpp"

#include "core/exceptions/invalid_argument_exception.hpp"

namespace engine::graphics::effect {

namespace exceptions = core::exceptions;

BloomEffect::BloomEffect(int shader_id, float intensity)
    : Effect(shader_id,
             blending::BlendParameters{
                 .equation = blending::enums::BlendEquation::Add,
                 .source = blending::enums::BlendMode::SourceAlpha,
                 .destination = blending::enums::BlendMode::OneMinusSourceAlpha,
             }),
      m_intensity(intensity) {
    if (intensity < 0.0f) {
        throw exceptions::InvalidArgumentException("Bloom intensity ({}) cannot be negative", intensity);
    }
}

void BloomEffect::apply_shader_parameters(shader::Shader &shader) const {
    shader.set_float("u_bloom_intensity", m_intensity);
}

float BloomEffect::intensity() const {
    return m_intensity;
}

} // namespace engine::graphics::effect
