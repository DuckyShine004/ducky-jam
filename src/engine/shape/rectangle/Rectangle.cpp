#include <engine/shape/rectangle/Rectangle.hpp>

#include <utility/datatype/ConvertUtility.hpp>

using namespace utility::datatype;

namespace engine::shape::rectangle {

Rectangle::Rectangle(glm::vec2 position) {
    this->_position = position;

    this->initialise();
}

void Rectangle::initialise() {
    this->_vertices = ConvertUtility::convertToVectorFloat1D(this->_VERTICES);
    this->_indices = ConvertUtility::convertToVectorUnsignedInt1D(this->_INDICES);

    this->translate(this->_position);
}

void Rectangle::translate(glm::vec2 offset) {
    int size = this->_vertices.size();

    for (int i = 0; i < size; i += 3) {
        this->_vertices[i] += offset.x;
        this->_vertices[i + 1] += offset.y;
    }
}

void Rectangle::scale(glm::vec2 scale) {
}

void Rectangle::scale(float scale) {
}

} // namespace engine::shape::rectangle