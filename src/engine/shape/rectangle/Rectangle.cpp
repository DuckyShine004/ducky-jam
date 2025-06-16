#include <engine/shape/rectangle/Rectangle.hpp>

#include <utility/datatype/ConvertUtility.hpp>

using namespace utility::datatype;

namespace engine::shape::rectangle {

constexpr float Rectangle::_VERTICES[];

constexpr unsigned int Rectangle::_INDICES[];

Rectangle::Rectangle(glm::vec2 position) : Shape(position) {
    this->initialise();
}

Rectangle::Rectangle(float x, float y) : Rectangle(glm::vec2(x, y)) {
}

Rectangle::~Rectangle() = default;

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

    this->_position += offset;
}

void Rectangle::scale(glm::vec2 scale) {
}

void Rectangle::scale(float scale) {
}

} // namespace engine::shape::rectangle