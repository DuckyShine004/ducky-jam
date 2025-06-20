#include <engine/shape/rectangle/Rectangle.hpp>

#include <utility/datatype/ConvertUtility.hpp>

using namespace utility::datatype;

namespace engine::shape::rectangle {

constexpr float Rectangle::_VERTICES[];

constexpr unsigned int Rectangle::_INDICES[];

Rectangle::Rectangle(glm::vec2 position, float width, float height) : Shape(position), _width(width), _height(height) {
    this->initialise();
}

Rectangle::Rectangle(float x, float y, float width, float height) : Shape(glm::vec2(x, y)), _width(width), _height(height) {
    this->initialise();
}

Rectangle::~Rectangle() = default;

void Rectangle::initialise() {
    this->_vertices = ConvertUtility::convertToVectorFloat1D(this->_VERTICES);
    this->_indices = ConvertUtility::convertToVectorUnsignedInt1D(this->_INDICES);

    for (int i = 0; i < 12; i += 3) {
        this->_vertices[i] += 0.5f;
        this->_vertices[i + 1] += 0.5f;
    }

    for (int i = 0; i < 12; i += 3) {
        this->_vertices[i] = this->_vertices[i] * this->_width + this->_position.x;
        this->_vertices[i + 1] = this->_vertices[i + 1] * this->_height + this->_position.y;
    }
}

void Rectangle::translate(glm::vec2 offset) {
    this->_position += offset;
}

void Rectangle::scale(glm::vec2 scale) {
}

void Rectangle::scale(float scale) {
}

} // namespace engine::shape::rectangle