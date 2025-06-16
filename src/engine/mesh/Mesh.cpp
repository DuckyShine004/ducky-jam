#include <engine/mesh/Mesh.hpp>

namespace engine::mesh {

Mesh::Mesh() {
    this->_vertexCount = 0;

    this->_indexCount = 0;

    glGenVertexArrays(1, &this->_vao);

    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
};

void Mesh::setVertices(std::vector<float> vertices) {
    this->_vertices = vertices;

    this->_vertexCount = vertices.size();
}

void Mesh::setIndices(std::vector<unsigned int> indices) {
    this->_indices = indices;

    this->_indexCount = indices.size();
}

void Mesh::setPrimitive(GLenum primitive) {
    this->_primitive = primitive;
}

void Mesh::setUsage(GLenum usage) {
    this->_usage = usage;
}

std::vector<float> &Mesh::getVertices() {
    return this->_vertices;
}

std::vector<unsigned int> &Mesh::getIndices() {
    return this->_indices;
}

GLenum Mesh::getPrimitive() {
    return this->_primitive;
}

GLenum Mesh::getUsage() {
    return this->_usage;
}

std::size_t Mesh::getVertexCount() {
    return this->_vertexCount;
}

std::size_t Mesh::getIndexCount() {
    return this->_indexCount;
}

} // namespace engine::mesh