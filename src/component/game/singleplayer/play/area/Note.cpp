#include <component/game/singleplayer/play/area/Note.hpp>

#include <engine/shape/rectangle/Rectangle.hpp>

#include <iostream>

using namespace engine::shape::rectangle;

namespace component::game::singleplayer::play::area {

Note::Note() = default;

void Note::create() {
    std::unique_ptr<Shape> shape = std::make_unique<Rectangle>(0.0f, 0.0f);

    addShape(std::move(shape));
}

} // namespace component::game::singleplayer::play::area