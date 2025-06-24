#include <engine/mesh/Mesh.hpp>

namespace engine::mesh {

Mesh::Mesh() : _vertexCount(0), _indexCount(0), _instanceCount(0), _isInitialised(false) {};

void Mesh::initialise(GLenum primitive, GLenum usage, int notes) {
    if (this->_isInitialised) {
        return;
    }

    this->setPrimitive(primitive);

    this->setUsage(usage);

    glGenVertexArrays(1, &this->_vao);

    glGenBuffers(1, &this->_vbo);
    glGenBuffers(1, &this->_ebo);
    glGenBuffers(1, &this->_instanceVbo);

    glBindVertexArray(this->_vao);

    glBindBuffer(GL_ARRAY_BUFFER, this->_vbo);
    glBufferData(GL_ARRAY_BUFFER, 0, nullptr, usage);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 0, nullptr, usage);

    glBindBuffer(GL_ARRAY_BUFFER, this->_instanceVbo);
    glBufferData(GL_ARRAY_BUFFER, notes * sizeof(Instance), nullptr, usage);

    // position (vec2) -> location 1
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Instance), (void *)offsetof(Instance, offset));
    glVertexAttribDivisor(1, 1);
    // size (float) -> location 2
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Instance), (void *)offsetof(Instance, size));
    glVertexAttribDivisor(2, 1);
    // colour (vec3) -> location 3
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Instance), (void *)offsetof(Instance, colour));
    glVertexAttribDivisor(3, 1);

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

void Mesh::setInstances(std::vector<Instance> instances) {
    this->_instances = instances;

    size_t instanceCount = instances.size();

    glBindBuffer(GL_ARRAY_BUFFER, this->_instanceVbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, instanceCount * sizeof(Instance), instances.data());

    this->_instanceCount = instanceCount;
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

std::vector<Instance> &Mesh::getInstances() {
    return this->_instances;
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

GLuint Mesh::getInstanceVbo() {
    return this->_instanceVbo;
}

std::size_t Mesh::getVertexCount() {
    return this->_vertexCount;
}

std::size_t Mesh::getIndexCount() {
    return this->_indexCount;
}

std::size_t Mesh::getInstanceCount() {
    return this->_instanceCount;
}

} // namespace engine::mesh