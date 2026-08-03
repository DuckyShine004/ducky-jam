#pragma once

#include <array>
#include <vector>

#include "engine/graphics/model/mesh.hpp"
#include "engine/graphics/model/quad.hpp"

#include "engine/graphics/drawable/sprite.hpp"

#include "engine/graphics/renderer/batch.hpp"
#include "engine/graphics/renderer/framebuffer.hpp"

namespace engine::graphics::renderer {

// NOTE: should check if target requires blooming, if not skip blooming
class Renderer {
  public:
    Renderer();
    ~Renderer();

    void initialise(int width, int height);
    void resize(int width, int height);

    void shutdown();

    void queue(const engine::graphics::model::Quad &quad);
    void queue(const engine::graphics::drawable::Sprite &sprite);

    void render();

  private:
    void render_scene();
    void render_batch(const engine::graphics::renderer::Batch &batch);
    GLuint render_blur();
    void render_composite(GLuint bloom_texture);
    void render_fullscreen_triangle() const;

    static inline constexpr int m_BLUR_PASSES = 8;
    static inline constexpr float m_BLOOM_STRENGTH = 1.0f;
    static inline constexpr float m_LOGICAL_WIDTH = 2560.0f;
    static inline constexpr float m_LOGICAL_HEIGHT = 1440.0f;

    engine::graphics::model::Mesh m_mesh;

    std::vector<engine::graphics::renderer::Batch> m_batches;

    Framebuffer m_hdr_framebuffer;
    std::array<Framebuffer, 2> m_blur_framebuffers;

    GLuint m_fullscreen_vao;

    int m_width;
    int m_height;

    bool m_initialised;
};

} // namespace engine::graphics::renderer
