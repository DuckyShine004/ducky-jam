#include "engine/graphics/renderer/renderer.hpp"

#include "core/exceptions/invalid_argument_exception.hpp"
#include "engine/graphics/drawable/sprite.hpp"
#include "engine/graphics/model/enums/topology_type.hpp"
#include "engine/graphics/shader/shader.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include <glm/ext/matrix_clip_space.hpp>

namespace engine::graphics::renderer {

namespace exceptions = core::exceptions;

using engine::graphics::model::enums::TopologyType;

Renderer::Renderer(int width, int height, shader::ShaderManager &shader_manager, texture::TextureManager &texture_manager, effect::EffectManager &effect_manager)
    : m_width(width), m_height(height), m_shader_manager(shader_manager), m_texture_manager(texture_manager), m_effect_manager(effect_manager) {
}

/* WARN: We expect bloom for now, later we add option to disable- performane issue on low end devices */
void Renderer::load() {
    m_bloom.emplace(m_width, m_height, m_fullscreen, m_shader_manager.get_shader("downsample"), m_shader_manager.get_shader("upsample"));
}

void Renderer::resize(int width, int height) {
    m_width = width;
    m_height = height;

    m_bloom->resize(width, height);
}

void Renderer::queue(const model::Quad &quad) {
    if (!quad.effect) {
        throw exceptions::InvalidArgumentException("Cannot queue a quad without an effect");
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
void Renderer::queue(const drawable::Sprite &sprite) {
    const texture::Texture &texture = m_texture_manager.get_texture(sprite.texture_path());
    const texture::UV &texture_uv = texture.get_region(sprite.texture_path()).uv;
    const texture::UV &sprite_uv = sprite.uv();

    texture::UV uv{
        .u0 = std::lerp(texture_uv.u0, texture_uv.u1, sprite_uv.u0),
        .u1 = std::lerp(texture_uv.u0, texture_uv.u1, sprite_uv.u1),
        .v0 = std::lerp(texture_uv.v0, texture_uv.v1, sprite_uv.v0),
        .v1 = std::lerp(texture_uv.v0, texture_uv.v1, sprite_uv.v1),
    };

    queue(model::Quad{
        .x = static_cast<float>(sprite.x() + sprite.offset_x()),
        .y = static_cast<float>(sprite.y() + sprite.offset_y()),
        .width = static_cast<float>(sprite.width()),
        .height = static_cast<float>(sprite.height()),
        .texture_id = texture.id(),
        .effect = sprite.effect(),
        .uv = uv,
    });
}

int Renderer::texture_id(const std::filesystem::path &path) const {
    return m_texture_manager.get_texture_id(path);
}

const texture::Texture &Renderer::texture(const std::filesystem::path &path) const {
    return m_texture_manager.get_texture(path);
}

int Renderer::shader_id(const std::string &name) const {
    return m_shader_manager.get_shader_id(name);
}

effect::EffectPtr Renderer::bloom_effect(float intensity) {
    return m_effect_manager.get_bloom_effect(intensity);
}

// WARN: Should render based on batch geometry instead of manual type
void Renderer::render() {
    render_scene();
    m_bloom->render();
    render_composite();

    m_batches.clear();
}

void Renderer::render_scene() {
    m_bloom->bind_hdr_framebuffer();

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
    const glm::mat4 projection = glm::ortho(0.0f, logical_width, 0.0f, logical_height, -1.0f, 1.0f);

    m_mesh.upload(batch.vertices(), batch.indices());

    shader::Shader &shader = m_shader_manager.use_shader(batch.key().effect->shader_id());
    batch.key().effect->apply(shader);

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

    shader::Shader &shader = m_shader_manager.use_shader("composite");

    shader.set_integer("u_scene", 0);
    shader.set_integer("u_bloom", 1);
    shader.set_float("u_bloom_strength", default_bloom_strength);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_bloom->hdr_texture());

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, m_bloom->blur_texture());

    m_fullscreen.render();

    glActiveTexture(GL_TEXTURE0);
}

} // namespace engine::graphics::renderer
