#include "engine/graphics/renderer/renderer.hpp"

#include "core/logger/logger_macros.hpp"
#include "engine/graphics/drawable/sprite.hpp"
#include "engine/graphics/model/enums/topology_type.hpp"
#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <stdexcept>

using namespace core::logger;

using namespace engine::graphics::shader;

using namespace engine::graphics::texture;

using namespace engine::graphics::drawable;

using namespace engine::graphics::model;
using namespace engine::graphics::model::enums;

namespace engine::graphics::renderer {

Renderer::Renderer(int width, int height, ShaderManager &shader_manager, TextureManager &texture_manager)
    : m_width(width), m_height(height), m_bloom(width, height, m_fullscreen, shader_manager.get_shader("downsample"), shader_manager.get_shader("upsample")), m_shader_manager(shader_manager), m_texture_manager(texture_manager) {
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;

    m_bloom.resize(width, height);
}

void Renderer::queue(const Quad &quad) {
    if (!quad.effect) {
        throw std::invalid_argument("Cannot queue a quad without an effect");
    }

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
    const UV &texture_uv = m_texture_manager.get_texture(sprite.texture_id()).get_region(sprite.texture_path()).uv;
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
    render_scene();
    m_bloom.render();
    render_composite();

    m_batches.clear();
}

void Renderer::render_scene() {
    m_bloom.bind_hdr_framebuffer();

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

    Shader &shader = m_shader_manager.get_active_shader();

    shader.set_matrix4fv("u_model", model);
    shader.set_matrix4fv("u_projection", projection);
    shader.set_integer("u_texture", 0);

    const int texture_id = m_texture_manager.get_texture(batch.key().texture_id).texture_id();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    m_mesh.render(TopologyType::Triangle);
}

void Renderer::render_composite() {
    Framebuffer::clear();

    glViewport(0, 0, m_width, m_height);

    glDisable(GL_BLEND);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Shader &shader = m_shader_manager.use_shader("composite");

    shader.set_integer("u_scene", 0);
    shader.set_integer("u_bloom", 1);
    shader.set_float("u_bloom_strength", m_BLOOM_STRENGTH);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_bloom.hdr_texture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_bloom.blur_texture());

    m_fullscreen.render();

    glActiveTexture(GL_TEXTURE0);
}

} // namespace engine::graphics::renderer
