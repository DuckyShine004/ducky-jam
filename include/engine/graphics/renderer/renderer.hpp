#pragma once

#include "engine/graphics/drawable/sprite.hpp"
#include "engine/graphics/model/mesh.hpp"
#include "engine/graphics/model/quad.hpp"
#include "engine/graphics/renderer/batch.hpp"
#include "engine/graphics/renderer/bloom.hpp"
#include "engine/graphics/renderer/framebuffer.hpp"
#include "engine/graphics/renderer/fullscreen.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include <vector>

namespace engine::graphics::renderer {

// NOTE: should check if target requires blooming, if not skip blooming
class Renderer {
  public:
    Renderer(int width, int height, engine::graphics::shader::ShaderManager &shader_manager, engine::graphics::texture::TextureManager &texture_manager);
    ~Renderer();

    void resize(int width, int height);

    void queue(const engine::graphics::model::Quad &quad);
    void queue(const engine::graphics::drawable::Sprite &sprite);

    void render();

  private:
    static inline constexpr float m_BLOOM_STRENGTH = 1.0f;

    static inline constexpr float m_LOGICAL_WIDTH = 2560.0f;
    static inline constexpr float m_LOGICAL_HEIGHT = 1440.0f;

    engine::graphics::model::Mesh m_mesh;

    std::vector<engine::graphics::renderer::Batch> m_batches;

    engine::graphics::renderer::Fullscreen m_fullscreen;
    engine::graphics::renderer::Bloom m_bloom;

    int m_width;
    int m_height;

    engine::graphics::shader::ShaderManager &m_shader_manager;
    engine::graphics::texture::TextureManager &m_texture_manager;

    void render_scene();
    void render_batch(const engine::graphics::renderer::Batch &batch);
    void render_composite();
};

} // namespace engine::graphics::renderer
