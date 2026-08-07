#pragma once

#include "engine/graphics/drawable/sprite.hpp"
#include "engine/graphics/effect/effect_manager.hpp"
#include "engine/graphics/model/mesh.hpp"
#include "engine/graphics/model/quad.hpp"
#include "engine/graphics/renderer/batch.hpp"
#include "engine/graphics/renderer/bloom.hpp"
#include "engine/graphics/renderer/fullscreen.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

#include <filesystem>
#include <optional>
#include <vector>

namespace engine::graphics::renderer {

// NOTE: should check if target requires blooming, if not skip blooming
class Renderer {
  public:
    Renderer(int width, int height, engine::graphics::shader::ShaderManager &shader_manager, engine::graphics::texture::TextureManager &texture_manager, engine::graphics::effect::EffectManager &effect_manager);

    void load();
    void resize(int width, int height);

    void queue(const engine::graphics::model::Quad &quad);
    void queue(const engine::graphics::drawable::Sprite &sprite);

    int texture_id(const std::filesystem::path &path) const;
    const engine::graphics::texture::Texture &texture(const std::filesystem::path &path) const;
    int shader_id(const std::string &name) const;
    engine::graphics::effect::EffectPtr bloom_effect(float intensity);

    void render();

  private:
    static inline constexpr float default_bloom_strength = 1.0f;

    static inline constexpr float logical_width = 2560.0f;
    static inline constexpr float logical_height = 1440.0f;

    engine::graphics::model::Mesh m_mesh;

    std::vector<engine::graphics::renderer::Batch> m_batches;

    engine::graphics::renderer::Fullscreen m_fullscreen;
    std::optional<engine::graphics::renderer::Bloom> m_bloom;

    int m_width;
    int m_height;

    engine::graphics::shader::ShaderManager &m_shader_manager;
    engine::graphics::texture::TextureManager &m_texture_manager;
    engine::graphics::effect::EffectManager &m_effect_manager;

    void render_scene();
    void render_batch(const engine::graphics::renderer::Batch &batch);
    void render_composite();
};

} // namespace engine::graphics::renderer
