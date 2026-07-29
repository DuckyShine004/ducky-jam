#pragma once

#include <memory>

#include <glm/glm.hpp>

#include "engine/graphic/shader/shader.hpp"
#include "engine/graphic/blending/blend_parameters.hpp"

namespace engine::graphic::effect {

class Effect {
  public:
    explicit Effect(int shader_id, engine::graphic::blending::BlendParameters blending = {});

    virtual ~Effect() = default;

    Effect(const Effect &) = delete;
    Effect &operator=(const Effect &) = delete;
    Effect(Effect &&) = delete;
    Effect &operator=(Effect &&) = delete;

    void apply() const;

    int shader_id() const;

    const engine::graphic::blending::BlendParameters &blend_parameters() const;

  protected:
    virtual void apply_shader_parameters(engine::graphic::shader::Shader &shader) const = 0;

  private:
    int m_shader_id;

    engine::graphic::blending::BlendParameters m_blend_parameters;
};

using EffectPtr = std::shared_ptr<const Effect>;

} // namespace engine::graphic::effect
