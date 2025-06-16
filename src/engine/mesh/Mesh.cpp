#include <engine/mesh/Mesh.hpp>

namespace engine::mesh {

Mesh::Mesh() {
    this->_vertexCount = 0;

    this->_indexCount = 0;

    this->_isInitialised = false;
};

void Mesh::initialise(GLenum primitive, GLenum usage) {
    if (this->_isInitialised) {
        return;
    }

    this->setPrimitive(primitive);

    this->setUsage(usage);

    glGenVertexArrays(1, &this->_vao);

    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, usage);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, usage);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    this->_isInitialised = true;
}

void Mesh::setVertices(std::vector<float> vertices) {
    this->_vertices = vertices;

    size_t vertexCount = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices.data(), this->_usage);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    this->_vertexCount = vertexCount;
}

void Mesh::setIndices(std::vector<unsigned int> indices) {
    this->_indices = indices;

    size_t indexCount = indices.size();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned int), indices.data(), this->_usage);

    this->_indexCount = indexCount;
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

GLuint Mesh::getVao() {
    return this->_vao;
}

std::size_t Mesh::getVertexCount() {
    return this->_vertexCount;
}

std::size_t Mesh::getIndexCount() {
    return this->_indexCount;
}

} // namespace engine::mesh