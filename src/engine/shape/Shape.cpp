#include <engine/shape/Shape.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace engine::shape {

Shape::Shape(glm::vec2 position, GLenum primitive) : _position(position), _primitive(primitive) {
}

Shape::Shape(float x, float y, GLenum primitive) : _position{x, y}, _primitive(primitive) {
}

Shape::~Shape() = default;

std::vector<float> Shape::getVertices() const {
    return this->_vertices;
}

std::vector<unsigned int> Shape::getIndices() const {
    return this->_indices;
}

GLenum Shape::getPrimitive() {
    return this->_primitive;
}

} // namespace engine::shape
