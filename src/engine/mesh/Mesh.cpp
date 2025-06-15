#include <engine/mesh/Mesh.hpp>

namespace engine::mesh {

Mesh::Mesh() {
    this->_vertexCount = 0;

    this->_indexCount = 0;
};

void Mesh::setVertices(std::vector<float> &vertices) {
    this->_vertices = vertices;

    this->_vertexCount = vertices.size();
}

void Mesh::setIndices(std::vector<unsigned int> &indices) {
    this->_indices = indices;

    this->_indexCount = indices.size();
}

std::vector<float> &Mesh::getVertices() {
    return this->_vertices;
}

std::vector<unsigned int> &Mesh::getIndices() {
    return this->_indices;
}

std::size_t Mesh::getVertexCount() {
    return this->_vertexCount;
}

std::size_t Mesh::getIndexCount() {
    return this->_indexCount;
}

} // namespace engine::mesh