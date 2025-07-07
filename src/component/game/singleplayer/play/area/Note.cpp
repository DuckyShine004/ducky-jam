#include "component/game/singleplayer/play/area/Note.hpp"

#include "engine/shape/rectangle/Rectangle.hpp"

#include <iostream>

using namespace engine::shape::rectangle;

namespace component::game::singleplayer::play::area {

Note::Note(float x, float width, int startTime, int endTime, glm::vec3 colour) : _startTime(startTime), _endTime(endTime), _colour(colour) {
    this->_position = glm::vec2(x, 0.0f);

    this->_size = glm::vec2(width, 48.0f);
}

int Note::getStartTime() {
    return this->_startTime;
}

int Note::getEndTime() {
    return this->_endTime;
}

glm::vec2 Note::getSize() {
    return this->_size;
}

glm::vec3 Note::getColour() {
    return this->_colour;
}

void Note::setHeight(float height) {
    this->_size.y = height;
}

float Note::getHeight() {
    return this->_size.y;
}

} // namespace component::game::singleplayer::play::area