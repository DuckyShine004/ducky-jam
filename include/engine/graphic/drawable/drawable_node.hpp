#pragma once

#include "engine/graphic/drawable/drawable.hpp"

namespace engine::graphic::drawable {

class DrawableNode : public Drawable {
  public:
    DrawableNode() = default;

    void submit(render::Renderer &renderer) const override;

  private:
    bool m_visible = true;
    float m_opacity = 1.0f;
    int m_z_index = 0;
};

} // namespace engine::graphic::drawable
