#include "engine/graphics/renderer/render_target.hpp"

#include <utility>

namespace engine::graphics::renderer {

RenderTarget::RenderTarget() : m_id(0), m_width(0), m_height(0), m_format(GL_R11F_G11F_B10F) {
}

RenderTarget::RenderTarget(int width, int height, GLenum format) : RenderTarget() {
    initialise(width, height, format);
}

RenderTarget::~RenderTarget() {
    destroy();
}

RenderTarget::RenderTarget(RenderTarget &&other) noexcept : m_id(std::exchange(other.m_id, 0)), m_width(std::exchange(other.m_width, 0)), m_height(std::exchange(other.m_height, 0)), m_format(other.m_format) {
}

RenderTarget &RenderTarget::operator=(RenderTarget &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroy();

    m_id = std::exchange(other.m_id, 0);

    m_width = std::exchange(other.m_width, 0);
    m_height = std::exchange(other.m_height, 0);

    m_format = other.m_format;

    return *this;
}

void RenderTarget::initialise(int width, int height, GLenum format) {
    m_width = width;
    m_height = height;

    m_format = format;

    if (m_id == 0) {
        glGenTextures(1, &m_id);
    }

    allocate();
}

void RenderTarget::resize(int width, int height) {
    if (width <= 0 || height <= 0 || (width == m_width && height == m_height)) {
        return;
    }

    m_width = width;
    m_height = height;

    allocate();
}

void RenderTarget::allocate() {
    glBindTexture(GL_TEXTURE_2D, m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    const GLenum type = m_format == GL_RGBA8 ? GL_UNSIGNED_BYTE : GL_FLOAT;
    const GLenum channels = m_format == GL_R11F_G11F_B10F ? GL_RGB : GL_RGBA;

    glTexImage2D(GL_TEXTURE_2D, 0, m_format, m_width, m_height, 0, channels, type, nullptr);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderTarget::destroy() {
    if (m_id != 0) {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

GLuint RenderTarget::id() const {
    return m_id;
}

int RenderTarget::width() const {
    return m_width;
}

int RenderTarget::height() const {
    return m_height;
}

} // namespace engine::graphics::renderer
