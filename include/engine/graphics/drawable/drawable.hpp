#pragma once

namespace engine::graphics::renderer {

class Renderer;

}

namespace engine::graphics::drawable {

class Drawable {
  public:
    virtual ~Drawable() = default;

    virtual void submit(engine::graphics::renderer::Renderer &renderer) const = 0;
};

} // namespace engine::graphics::drawable
