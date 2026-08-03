#pragma once

#include <cstddef>
#include <vector>

#include "engine/graphics/renderer/render_target.hpp"

namespace engine::graphics::renderer {

class Framebuffer {
  public:
    Framebuffer();
    ~Framebuffer();

    Framebuffer(const Framebuffer &) = delete;
    Framebuffer &operator=(const Framebuffer &) = delete;

    Framebuffer(Framebuffer &&other) noexcept;
    Framebuffer &operator=(Framebuffer &&other) noexcept;

    void initialise();
    void destroy();

    void add_render_target(int width, int height, GLenum format = GL_RGBA16F);
    void resize(int width, int height);
    void validate() const;

    RenderTarget &render_target(std::size_t index);
    const RenderTarget &render_target(std::size_t index) const;

    void bind() const;
    static void clear();

    GLuint id() const;

  private:
    GLuint m_id;

    std::vector<RenderTarget> m_render_targets;
};

} // namespace engine::graphics::renderer
