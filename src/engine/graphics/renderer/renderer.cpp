#include <algorithm>
#include <stdexcept>

#include <glm/ext/matrix_clip_space.hpp>

#include "engine/graphics/effect/effect.hpp"

#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/shader/shader_manager.hpp"

#include "engine/graphics/texture/texture_manager.hpp"

#include "engine/graphics/drawable/sprite.hpp"

#include "engine/graphics/model/enums/topology_type.hpp"

#include "engine/graphics/renderer/renderer.hpp"

using namespace engine::graphics::shader;

using namespace engine::graphics::texture;

using namespace engine::graphics::drawable;

using namespace engine::graphics::model;
using namespace engine::graphics::model::enums;

namespace engine::graphics::renderer {

Renderer::Renderer() : m_fullscreen_vao(0), m_width(0), m_height(0), m_initialised(false) {
}

Renderer::~Renderer() = default;

void Renderer::initialise(int width, int height) {
    if (m_initialised) {
        resize(width, height);
        return;
    }

    if (width <= 0 || height <= 0) {
        throw std::invalid_argument("Renderer dimensions must be positive");
    }

    m_width = width;
    m_height = height;

    m_hdr_framebuffer.add_render_target(width, height, GL_RGBA8);
    m_hdr_framebuffer.add_render_target(width, height, GL_RGBA16F);

    const int bloom_width = std::max(1, width / 2);
    const int bloom_height = std::max(1, height / 2);

    for (Framebuffer &framebuffer : m_blur_framebuffers) {
        framebuffer.add_render_target(bloom_width, bloom_height, GL_RGBA16F);
    }

    m_hdr_framebuffer.validate();

    m_blur_framebuffers[0].validate();
    m_blur_framebuffers[1].validate();

    glGenVertexArrays(1, &m_fullscreen_vao);

    m_initialised = true;
}

void Renderer::resize(int width, int height) {
    if (!m_initialised || width <= 0 || height <= 0 || (width == m_width && height == m_height)) {
        return;
    }

    m_width = width;
    m_height = height;

    m_hdr_framebuffer.resize(width, height);

    const int bloom_width = std::max(1, width / 2);
    const int bloom_height = std::max(1, height / 2);

    for (Framebuffer &framebuffer : m_blur_framebuffers) {
        framebuffer.resize(bloom_width, bloom_height);
    }
}

void Renderer::shutdown() {
    if (m_fullscreen_vao != 0) {
        glDeleteVertexArrays(1, &m_fullscreen_vao);
        m_fullscreen_vao = 0;
    }

    m_hdr_framebuffer.destroy();

    for (Framebuffer &framebuffer : m_blur_framebuffers) {
        framebuffer.destroy();
    }

    m_initialised = false;
}

void Renderer::queue(const Quad &quad) {
    if (!quad.effect)
        throw std::invalid_argument("Cannot queue a quad without an effect");

    BatchKey batch_key{
        .effect = quad.effect,
        .texture_id = quad.texture_id,
    };

    if (m_batches.empty() || m_batches.back().key() != batch_key) {
        m_batches.emplace_back(batch_key);
    }

    m_batches.back().add(quad);
}

// NOTE: Should maybe pass drawable instead of sprite, because sprite in this case refers to quad
// But then if I want to debug e.g., AABB then I need to pass draw lines
void Renderer::queue(const Sprite &sprite) {
    const UV &texture_uv = TextureManager::get_instance().get_texture(sprite.texture_id()).get_region(sprite.texture_path()).uv;
    const UV &sprite_uv = sprite.uv();

    UV uv{
        .u0 = std::lerp(texture_uv.u0, texture_uv.u1, sprite_uv.u0),
        .u1 = std::lerp(texture_uv.u0, texture_uv.u1, sprite_uv.u1),
        .v0 = std::lerp(texture_uv.v0, texture_uv.v1, sprite_uv.v0),
        .v1 = std::lerp(texture_uv.v0, texture_uv.v1, sprite_uv.v1),
    };

    queue(Quad{
        .x = static_cast<float>(sprite.x() + sprite.offset_x()),
        .y = static_cast<float>(sprite.y() + sprite.offset_y()),
        .width = static_cast<float>(sprite.width()),
        .height = static_cast<float>(sprite.height()),
        .texture_id = sprite.texture_id(),
        .effect = sprite.effect(),
        .uv = uv,
    });
}

// WARN: Should render based on batch geometry instead of manual type
void Renderer::render() {
    if (!m_initialised) {
        throw std::runtime_error("Renderer must be initialised before rendering");
    }

    render_scene();

    const GLuint bloom_texture = render_blur();

    render_composite(bloom_texture);

    m_batches.clear();
}

void Renderer::render_scene() {
    m_hdr_framebuffer.bind();

    glViewport(0, 0, m_width, m_height);

    constexpr GLfloat clear_colour[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    glClearBufferfv(GL_COLOR, 0, clear_colour);
    glClearBufferfv(GL_COLOR, 1, clear_colour);

    for (const Batch &batch : m_batches) {
        render_batch(batch);
    }
}

void Renderer::render_batch(const Batch &batch) {
    const glm::mat4 model = glm::mat4(1.0f);
    const glm::mat4 projection = glm::ortho(0.0f, m_LOGICAL_WIDTH, 0.0f, m_LOGICAL_HEIGHT, -1.0f, 1.0f);

    m_mesh.upload(batch.vertices(), batch.indices());

    batch.key().effect->apply();

    Shader &shader = ShaderManager::get_instance().get_active_shader();

    shader.set_matrix4fv("u_model", model);
    shader.set_matrix4fv("u_projection", projection);
    shader.set_integer("u_texture", 0);

    const int texture_id = TextureManager::get_instance().get_texture(batch.key().texture_id).texture_id();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    m_mesh.render(TopologyType::Triangle);
}

GLuint Renderer::render_blur() {
    Shader &shader = ShaderManager::get_instance().use_shader("blur");

    shader.set_integer("u_texture", 0);

    glDisable(GL_BLEND);

    GLuint input_texture = m_hdr_framebuffer.render_target(1).id();

    for (int pass = 0; pass < m_BLUR_PASSES; ++pass) {
        const bool horizontal = (pass % 2) == 0;
        const std::size_t target_index = horizontal ? 0 : 1;
        const RenderTarget &target = m_blur_framebuffers[target_index].render_target(0);

        m_blur_framebuffers[target_index].bind();
        glViewport(0, 0, target.width(), target.height());

        shader.set_integer("u_horizontal", horizontal ? 1 : 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, input_texture);

        render_fullscreen_triangle();

        input_texture = m_blur_framebuffers[target_index].render_target(0).id();
    }

    return input_texture;
}

void Renderer::render_composite(GLuint bloom_texture) {
    Framebuffer::clear();

    glViewport(0, 0, m_width, m_height);

    glDisable(GL_BLEND);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader &shader = ShaderManager::get_instance().use_shader("composite");

    shader.set_integer("u_scene", 0);
    shader.set_integer("u_bloom", 1);
    shader.set_float("u_bloom_strength", m_BLOOM_STRENGTH);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_hdr_framebuffer.render_target(0).id());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, bloom_texture);

    render_fullscreen_triangle();

    glActiveTexture(GL_TEXTURE0);
}

void Renderer::render_fullscreen_triangle() const {
    glBindVertexArray(m_fullscreen_vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

} // namespace engine::graphics::renderer
