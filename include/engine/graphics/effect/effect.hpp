#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/blending/blend_parameters.hpp"

namespace engine::graphics::effect {

class Effect {
  public:
    explicit Effect(int shader_id, engine::graphics::blending::BlendParameters blending = {});

    virtual ~Effect() = default;

    Effect(const Effect &) = delete;
    Effect &operator=(const Effect &) = delete;
    Effect(Effect &&) = delete;
    Effect &operator=(Effect &&) = delete;

    void apply(engine::graphics::shader::Shader &shader) const;

    int shader_id() const;

    const engine::graphics::blending::BlendParameters &blend_parameters() const;

  protected:
    virtual void apply_shader_parameters(engine::graphics::shader::Shader &shader) const = 0;

  private:
    int m_shader_id;

    engine::graphics::blending::BlendParameters m_blend_parameters;
};

using EffectPtr = std::shared_ptr<const Effect>;

} // namespace engine::graphics::effect
