#pragma once

#include "engine/graphics/renderer/framebuffer.hpp"
#include "engine/graphics/renderer/fullscreen.hpp"
#include "engine/graphics/shader/shader.hpp"

namespace engine::graphics::renderer {

class Bloom {
  public:
    Bloom(int width, int height, engine::graphics::renderer::Fullscreen &fullscreen, engine::graphics::shader::Shader &downsample_shader, engine::graphics::shader::Shader &upsample_shader);

    void resize(int width, int height);
    void bind_hdr_framebuffer();
    void render();

    GLuint hdr_texture();
    GLuint blur_texture();

  private:
    static inline constexpr int default_mip_levels = 5;

    // smaller for sharper bloom but also more costly so probably just keep it broad
    static inline constexpr float default_filter_radius = 1.0f;

    engine::graphics::renderer::Framebuffer m_hdr_framebuffer;
    engine::graphics::renderer::Framebuffer m_blur_framebuffer;

    engine::graphics::shader::Shader m_downsample_shader;
    engine::graphics::shader::Shader m_upsample_shader;

    engine::graphics::renderer::Fullscreen m_fullscreen;

    void render_upsamples(engine::graphics::shader::Shader &shader);
    void render_downsamples(engine::graphics::shader::Shader &shader);
};

} // namespace engine::graphics::renderer
