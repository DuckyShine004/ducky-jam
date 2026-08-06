#pragma once

#include <vector>
#include <cstddef>

#include "engine/graphics/renderer/mip.hpp"
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

    void add_mip(int width, int height, GLenum format = GL_R11F_G11F_B10F);
    void add_render_target(int width, int height, GLenum format = GL_R11F_G11F_B10F);
    void resize(int width, int height);
    void validate() const;
    void validate_render_target(std::size_t index) const;

    std::vector<Mip> &mips();
    const std::vector<Mip> &mips() const;

    RenderTarget &render_target(std::size_t index);
    const RenderTarget &render_target(std::size_t index) const;

    void bind() const;
    void bind_render_target(std::size_t index) const;
    static void clear();

    GLuint id() const;

  private:
    GLuint m_id;

    std::vector<Mip> m_mips;
    std::vector<RenderTarget> m_render_targets;
};

} // namespace engine::graphics::renderer
