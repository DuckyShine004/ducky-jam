#include "engine/graphics/renderer/framebuffer.hpp"

#include "core/exceptions/runtime_exception.hpp"

#include <utility>

namespace engine::graphics::renderer {

namespace exceptions = core::exceptions;

Framebuffer::Framebuffer() : m_id(0) {
}

Framebuffer::~Framebuffer() {
    destroy();
}

Framebuffer::Framebuffer(Framebuffer &&other) noexcept : m_id(std::exchange(other.m_id, 0)), m_mips(std::move(other.m_mips)), m_render_targets(std::move(other.m_render_targets)) {
}

Framebuffer &Framebuffer::operator=(Framebuffer &&other) noexcept {
    if (this == &other) {
        return *this;
    }

    destroy();

    m_id = std::exchange(other.m_id, 0);
    m_mips = std::move(other.m_mips);
    m_render_targets = std::move(other.m_render_targets);

    return *this;
}

void Framebuffer::initialise() {
    if (m_id == 0) {
        glGenFramebuffers(1, &m_id);
    }
}

void Framebuffer::destroy() {
    m_mips.clear();
    m_render_targets.clear();

    if (m_id != 0) {
        glDeleteFramebuffers(1, &m_id);
        m_id = 0;
    }
}

void Framebuffer::add_mip(int width, int height, GLenum format) {
    initialise();

    m_mips.emplace_back(width, height);
    m_render_targets.emplace_back(width, height, format);
}

void Framebuffer::add_render_target(int width, int height, GLenum format) {
    initialise();

    m_render_targets.emplace_back(width, height, format);

    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    const std::size_t index = m_render_targets.size() - 1;

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(index), GL_TEXTURE_2D, m_render_targets[index].id(), 0);

    clear();
}

void Framebuffer::resize(int width, int height) {
    for (RenderTarget &target : m_render_targets) {
        target.resize(width, height);
    }
}

void Framebuffer::validate() const {
    bind();

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        clear();
        throw exceptions::RuntimeException("Framebuffer is incomplete");
    }

    clear();
}

void Framebuffer::validate_render_target(std::size_t index) const {
    bind_render_target(index);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        clear();
        throw exceptions::RuntimeException("Framebuffer render target is incomplete");
    }

    clear();
}

std::vector<Mip> &Framebuffer::mips() {
    return m_mips;
}

const std::vector<Mip> &Framebuffer::mips() const {
    return m_mips;
}

RenderTarget &Framebuffer::render_target(std::size_t index) {
    return m_render_targets.at(index);
}

const RenderTarget &Framebuffer::render_target(std::size_t index) const {
    return m_render_targets.at(index);
}

void Framebuffer::bind() const {
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);

    std::vector<GLenum> attachments(m_render_targets.size());

    for (std::size_t i = 0; i < m_render_targets.size(); ++i) {
        attachments[i] = GL_COLOR_ATTACHMENT0 + static_cast<GLenum>(i);
    }

    if (!attachments.empty()) {
        glDrawBuffers(static_cast<GLsizei>(attachments.size()), attachments.data());
    }
}

void Framebuffer::bind_render_target(std::size_t index) const {
    const RenderTarget &target = m_render_targets.at(index);

    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, target.id(), 0);

    constexpr GLenum attachment = GL_COLOR_ATTACHMENT0;
    glDrawBuffers(1, &attachment);
}

void Framebuffer::clear() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint Framebuffer::id() const {
    return m_id;
}

} // namespace engine::graphics::renderer
