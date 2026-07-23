#include "engine/graphic/render/batch.hpp"
#include "engine/graphic/texture/texture_manager.hpp"

using namespace engine::graphic::model;
using namespace engine::graphic::texture;

namespace engine::graphic::render {

Batch::Batch(BatchKey &key) : m_key(key) {
}

void Batch::add(const Sprite &sprite) {
    const glm::vec2 &position = sprite.position();

    const UV &uv = TextureManager::get_instance().get_texture(sprite.texture_id()).get_uv(sprite.texture_path());

    double x0 = position.x;
    double x1 = x0 + sprite.width();
    double y0 = position.y;
    double y1 = y0 + sprite.height();

    int offset = m_vertices.size();

    m_vertices.emplace_back(x0, y0, uv.u0, uv.v0);
    m_vertices.emplace_back(x1, y0, uv.u1, uv.v0);
    m_vertices.emplace_back(x1, y1, uv.u1, uv.v1);
    m_vertices.emplace_back(x0, y1, uv.u0, uv.v1);

    m_indices.emplace_back(0 + offset);
    m_indices.emplace_back(1 + offset);
    m_indices.emplace_back(2 + offset);
    m_indices.emplace_back(2 + offset);
    m_indices.emplace_back(3 + offset);
    m_indices.emplace_back(0 + offset);
}

const BatchKey &Batch::key() const {
    return m_key;
}

const std::vector<Vertex> &Batch::vertices() const {
    return m_vertices;
}

const std::vector<GLuint> &Batch::indices() const {
    return m_indices;
}

} // namespace engine::graphic::render
