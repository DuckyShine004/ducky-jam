#include <engine/shape/Shape.hpp>

#include <glm/glm.hpp>

#include <vector>

namespace engine::shape {

Shape::~Shape() = default;

std::vector<float> Shape::getVertices() const {
    return this->_vertices;
}

std::vector<unsigned int> Shape::getIndices() const {
    return this->_indices;
}

} // namespace engine::shape
