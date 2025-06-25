#include <component/Component.hpp>

namespace component {

Component::Component() = default;

Component::~Component() = default;

void Component::addShape(std::unique_ptr<Shape> shape) {
    this->_shapes.push_back(std::move(shape));
}

void Component::create() {
}

void Component::load() {
}

void Component::update(float deltaTime) {
}

void Component::generateMesh() {
}

std::vector<std::unique_ptr<Shape>> &Component::getShapes() {
    return this->_shapes;
}

glm::vec2 Component::getPosition() {
    return this->_position;
}

void Component::setX(float x) {
    this->_position.x = x;
}

void Component::setY(float y) {
    this->_position.y = y;
}

} // namespace component