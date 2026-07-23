#include <cstddef>

#include "engine/graphic/model/mesh.hpp"
#include "engine/graphic/model/vertex.hpp"

#include "core/logger/logger_macros.hpp"

namespace engine::graphic::model {

using engine::graphic::model::enums::TopologyType;

Mesh::Mesh() : m_vao(0), m_vbo(0), m_ibo(0), m_indices_length(0) {
}

void Mesh::upload() {
    upload(m_vertices, m_indices);
}

// WARN: m_vertices != vertices, if members are used anywhere else in code, must move or create copy
void Mesh::upload(const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices) {
    m_indices_length = indices.size();

    if (m_vao == 0) {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ibo);

        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);

        glEnableVertexAttribArray(m_POSITION_ATTRIBUTE);
        glEnableVertexAttribArray(m_UV_ATTRIBUTE);

        glVertexAttribPointer(m_POSITION_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glVertexAttribPointer(m_UV_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLsizeiptr vertices_size = static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex));
    GLsizeiptr indices_size = static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint));

    glBindVertexArray(m_vao);

    /* NOTE: could be dynamic or stream, idk dynamic i guess? */
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices.data(), GL_DYNAMIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Mesh::render(const TopologyType &topology) {
    switch (topology) {
        case TopologyType::Triangle:
            draw_triangles();
            break;
        case TopologyType::Line:
            draw_lines();
            break;
    }
}

void Mesh::draw_lines() {
    glBindVertexArray(m_vao);
    glDrawElements(GL_LINES, m_indices_length, GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
}

void Mesh::draw_triangles() {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices_length, GL_UNSIGNED_INT, (void *)0);
    glBindVertexArray(0);
}

void Mesh::add_vertex(Vertex &vertex) {
    m_vertices.push_back(vertex);
}

void Mesh::add_vertex(glm::vec2 &position) {
    m_vertices.emplace_back(position);
}

void Mesh::add_vertex(float x, float y) {
    m_vertices.emplace_back(x, y);
}

void Mesh::add_vertex(float x, float y, const glm::vec2 &uv) {
    m_vertices.emplace_back(x, y, uv.x, uv.y);
}

void Mesh::add_vertex(float x, float y, float u, float v) {
    m_vertices.emplace_back(x, y, u, v);
}

void Mesh::add_index(GLuint index) {
    m_indices.push_back(index);
}

std::vector<Vertex> &Mesh::get_vertices() {
    return m_vertices;
}

std::vector<GLuint> &Mesh::get_indices() {
    return m_indices;
}

void Mesh::clear_vertices() {
    m_vertices.clear();
}

void Mesh::clear() {
    m_vertices.clear();
    m_indices.clear();
}

} // namespace engine::graphic::model
