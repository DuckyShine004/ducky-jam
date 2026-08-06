#pragma once

#include "external/glad/glad.h"

namespace engine::graphics::renderer {

class RenderTarget {
  public:
    RenderTarget();
    RenderTarget(int width, int height, GLenum format = GL_R11F_G11F_B10F);
    ~RenderTarget();

    RenderTarget(const RenderTarget &) = delete;
    RenderTarget &operator=(const RenderTarget &) = delete;

    RenderTarget(RenderTarget &&other) noexcept;
    RenderTarget &operator=(RenderTarget &&other) noexcept;

    void initialise(int width, int height, GLenum format = GL_R11F_G11F_B10F);
    void resize(int width, int height);
    void destroy();

    GLuint id() const;
    int width() const;
    int height() const;

  private:
    void allocate();

    GLuint m_id;

    int m_width;
    int m_height;

    GLenum m_format;
};

} // namespace engine::graphics::renderer
