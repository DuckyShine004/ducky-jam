#include "engine/graphics/renderer/bloom.hpp"

namespace engine::graphics::renderer {

Bloom::Bloom(int width, int height, Fullscreen &fullscreen, shader::Shader &downsample_shader, shader::Shader &upsample_shader) : m_fullscreen(fullscreen), m_downsample_shader(downsample_shader), m_upsample_shader(upsample_shader) {
    m_hdr_framebuffer.add_render_target(width, height, GL_RGBA8);
    m_hdr_framebuffer.add_render_target(width, height, GL_RGBA16F);

    int mip_width = width;
    int mip_height = height;

    for (int i = 0; i < default_mip_levels; ++i) {
        mip_width = std::max(1, mip_width / 2);
        mip_height = std::max(1, mip_height / 2);

        m_blur_framebuffer.add_mip(mip_width, mip_height, GL_R11F_G11F_B10F);
    }

    m_hdr_framebuffer.validate();

    for (std::size_t i = 0; i < m_blur_framebuffer.mips().size(); ++i) {
        m_blur_framebuffer.validate_render_target(i);
    }
}

void Bloom::resize(int width, int height) {
    m_hdr_framebuffer.resize(width, height);

    std::vector<Mip> &mips = m_blur_framebuffer.mips();

    int mip_width = width;
    int mip_height = height;

    for (std::size_t i = 0; i < mips.size(); ++i) {
        mip_width = std::max(1, mip_width / 2);
        mip_height = std::max(1, mip_height / 2);

        mips[i].width = mip_width;
        mips[i].height = mip_height;

        m_blur_framebuffer.render_target(i).resize(mip_width, mip_height);
    }
}

void Bloom::bind_hdr_framebuffer() {
    m_hdr_framebuffer.bind();
}

void Bloom::render() {
    render_downsamples(m_downsample_shader);
    render_upsamples(m_upsample_shader);
}

void Bloom::render_upsamples(engine::graphics::shader::Shader &shader) {
    shader.set_integer("u_texture", 0);
    shader.set_float("u_filter_radius", default_filter_radius);

    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    const std::vector<Mip> &mips = m_blur_framebuffer.mips();

    glActiveTexture(GL_TEXTURE0);

    for (std::size_t source_index = mips.size() - 1; source_index > 0; --source_index) {
        const std::size_t destination_index = source_index - 1;
        const Mip &destination_mip = mips[destination_index];

        m_blur_framebuffer.bind_render_target(destination_index);
        glViewport(0, 0, destination_mip.width, destination_mip.height);

        glBindTexture(GL_TEXTURE_2D, m_blur_framebuffer.render_target(source_index).id());
        m_fullscreen.render();
    }

    glDisable(GL_BLEND);
}

void Bloom::render_downsamples(shader::Shader &shader) {
    shader.set_integer("u_texture", 0);

    glDisable(GL_BLEND);

    GLuint source_texture = m_hdr_framebuffer.render_target(1).id();
    const std::vector<Mip> &mips = m_blur_framebuffer.mips();

    glActiveTexture(GL_TEXTURE0);

    for (std::size_t i = 0; i < mips.size(); ++i) {
        const Mip &mip = mips[i];

        m_blur_framebuffer.bind_render_target(i);
        glViewport(0, 0, mip.width, mip.height);

        glBindTexture(GL_TEXTURE_2D, source_texture);
        m_fullscreen.render();

        source_texture = m_blur_framebuffer.render_target(i).id();
    }
}

GLuint Bloom::hdr_texture() {
    return m_hdr_framebuffer.render_target(0).id();
}

GLuint Bloom::blur_texture() {
    return m_blur_framebuffer.render_target(0).id();
}

} // namespace engine::graphics::renderer
