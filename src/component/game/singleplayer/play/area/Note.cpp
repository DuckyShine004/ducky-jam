#include <component/game/singleplayer/play/area/Note.hpp>

#include <engine/shape/rectangle/Rectangle.hpp>

using namespace engine::shape::rectangle;

namespace component::game::singleplayer::play::area {

Note::Note() = default;

void Note::create() {
    std::unique_ptr<Shape> shape = std::make_unique<Rectangle>(0.0f, 0.0f);

    addShape(std::move(shape));
}

void Note::load() {
    generateMesh();
}

void Note::generateMesh() {
    const Shape *shape = this->_shapes[0].get();

    this->_mesh.setVertices(shape->getVertices());

    this->_mesh.setIndices(shape->getIndices());
}

} // namespace component::game::singleplayer::play::area