#include <glm/ext/matrix_clip_space.hpp>

#include "engine/graphic/effect/effect.hpp"
#include "engine/graphic/effect/effect_manager.hpp"

#include "engine/graphic/shader/shader.hpp"
#include "engine/graphic/shader/shader_manager.hpp"

#include "engine/graphic/texture/texture_manager.hpp"

#include "engine/graphic/drawable/sprite.hpp"

#include "engine/graphic/model/enums/topology_type.hpp"

#include "engine/graphic/render/renderer.hpp"

using namespace engine::graphic::shader;
using namespace engine::graphic::effect;

using namespace engine::graphic::texture;

using namespace engine::graphic::drawable;

using namespace engine::graphic::model;
using namespace engine::graphic::model::enums;

namespace engine::graphic::render {

Renderer::Renderer() = default;

void Renderer::queue(const Quad &quad) {
    BatchKey batch_key{
        .effect_id = quad.effect_id,
        .texture_id = quad.texture_id,
    };

    if (m_batches.empty() || m_batches.back().key() != batch_key) {
        Batch &batch = m_batches.emplace_back(batch_key);
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
        .effect_id = sprite.effect_id(),
        .uv = uv,
    });
}

// WARN: Should render based on batch geometry instead of manual type
void Renderer::render() {
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 2560.0f, 0.0f, 1440.0f, -1.0f, 1.0f);

    // NOTE: Apply effect, then set transforms, then bind texture, then render mesh
    for (const Batch &batch : m_batches) {
        m_mesh.upload(batch.vertices(), batch.indices());

        // FIX: Effect could be empty
        EffectManager::get_instance().get_effect(batch.key().effect_id).apply();

        Shader &shader = ShaderManager::get_instance().get_active_shader();

        shader.set_matrix4fv("u_model", model);
        shader.set_matrix4fv("u_projection", projection);
        shader.set_integer("u_texture", 0);

        int texture_id = TextureManager::get_instance().get_texture(batch.key().texture_id).texture_id();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture_id);

        m_mesh.render(TopologyType::Triangle);
    }

    m_batches.clear();
}

} // namespace engine::graphic::render
