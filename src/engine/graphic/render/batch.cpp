#include "engine/graphic/render/batch.hpp"

using namespace engine::graphic::model;
using namespace engine::graphic::texture;

namespace engine::graphic::render {

Batch::Batch(const BatchKey &key) : m_key(key) {
}

void Batch::add(const Quad &quad) {
    float x0 = quad.x;
    float y0 = quad.y;
    float x1 = x0 + quad.width;
    float y1 = y0 + quad.height;

    GLuint offset = static_cast<GLuint>(m_vertices.size());

    m_vertices.emplace_back(x0, y0, quad.uv.u0, quad.uv.v0, quad.colour);
    m_vertices.emplace_back(x1, y0, quad.uv.u1, quad.uv.v0, quad.colour);
    m_vertices.emplace_back(x1, y1, quad.uv.u1, quad.uv.v1, quad.colour);
    m_vertices.emplace_back(x0, y1, quad.uv.u0, quad.uv.v1, quad.colour);

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
