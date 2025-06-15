#include <component/Component.hpp>

namespace component {

Component::Component() = default;

Component::~Component() = default;

void Component::addShape(std::unique_ptr<Shape> shape) {
    this->_shapes.push_back(std::move(shape));
}

std::vector<std::unique_ptr<Shape>> &Component::getShapes() {
    return this->_shapes;
}

Mesh Component::getMesh() {
    return this->_mesh;
}

} // namespace component