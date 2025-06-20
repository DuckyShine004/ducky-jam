#include <component/game/singleplayer/play/area/Note.hpp>

#include <engine/shape/rectangle/Rectangle.hpp>

#include <iostream>

using namespace engine::shape::rectangle;

namespace component::game::singleplayer::play::area {

Note::Note(float x, float y, float width, float height) : _width(width), _height(height) {
    this->_position = glm::vec2(x, y);

    std::unique_ptr<Shape> shape = std::make_unique<Rectangle>(x, y, width, height);

    addShape(std::move(shape));
}

void Note::create() {
}

void Note::update(float deltaTime) {
    // glm::vec2 offset(0.0f, -0.01f);

    // for (std::unique_ptr<Shape> &shape : this->_shapes) {
    //     shape->translate(offset);
    // }
}

} // namespace component::game::singleplayer::play::area