#include "engine/graphics/renderer/fullscreen.hpp"

namespace engine::graphics::renderer {

Fullscreen::Fullscreen() : m_vao(0) {
    glGenVertexArrays(1, &m_vao);
}

Fullscreen::~Fullscreen() {
    if (m_vao != 0) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

void Fullscreen::render() {
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

} // namespace engine::graphics::renderer
