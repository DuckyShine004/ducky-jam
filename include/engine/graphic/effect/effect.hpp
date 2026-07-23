#pragma once

namespace engine::graphic::effect {

class Effect {
  public:
    explicit Effect(int shader_id);
    virtual ~Effect() = default;

    virtual void apply() const = 0;

    int shader_id() const;

  protected:
    int m_shader_id;
};

} // namespace engine::graphic::effect
