#pragma once

#include "external/glad/glad.h"

// NOTE: fullscreen quad (for postprocessing ONLY)
namespace engine::graphics::renderer {

class Fullscreen {
  public:
    Fullscreen();
    ~Fullscreen();

    void render();

  private:
    GLuint m_vao;
};

} // namespace engine::graphics::renderer
