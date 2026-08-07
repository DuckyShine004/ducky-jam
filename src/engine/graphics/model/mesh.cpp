#include "engine/graphics/model/mesh.hpp"

#include "engine/graphics/model/vertex.hpp"

#include <cstddef>

namespace engine::graphics::model {

using engine::graphics::model::enums::TopologyType;

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

        glEnableVertexAttribArray(position_attribute);
        glEnableVertexAttribArray(uv_attribute);
        glEnableVertexAttribArray(colour_attribute);

        glVertexAttribPointer(position_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, position));
        glVertexAttribPointer(uv_attribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, uv));
        glVertexAttribPointer(colour_attribute, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void *)offsetof(Vertex, colour));

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    GLsizeiptr vertices_size = static_cast<GLsizeiptr>(vertices.size() * sizeof(Vertex));
    GLsizeiptr indices_size = static_cast<GLsizeiptr>(indices.size() * sizeof(GLuint));

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices.data(), GL_STREAM_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices.data(), GL_STREAM_DRAW);

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

void Mesh::add_vertex(float x, float y, float u, float v, const core::structs::Vector4<std::uint8_t> &colour) {
    m_vertices.emplace_back(x, y, u, v, colour);
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

} // namespace engine::graphics::model
