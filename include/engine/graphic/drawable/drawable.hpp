#pragma once

namespace engine::graphic::render {

class Renderer;

}

namespace engine::graphic::drawable {

class Drawable {
  public:
    virtual ~Drawable() = default;

    virtual void submit(engine::graphic::render::Renderer &renderer) const = 0;
};

} // namespace engine::graphic::drawable
