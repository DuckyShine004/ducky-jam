#pragma once

#include <engine/shape/rectangle/Rectangle.hpp>

#include <glm/glm.hpp>

namespace engine::shape::rectangle {

Rectangle::Rectangle(glm::vec2 position) {
    this->_position = position;

    this->_vertices = v
}

void Rectangle::translate(glm::vec2 offset) const {
}

void Rectangle::scale(glm::vec2 scale) const {
}

void Rectangle::scale(float scale) const {
}

} // namespace engine::shape::rectangle