#include <component/game/singleplayer/play/area/Area.hpp>

namespace component::game::singleplayer::play::area {

Area::Area() = default;

void Area::create() {
    for (int i = 0; i < 1; i++) {
        std::unique_ptr<Lane> lane = std::make_unique<Lane>();

        lane->create();

        this->_lanes.push_back(std::move(lane));
    }
}

void Area::load() {
}

void Area::generateMesh() {
    generateNoteMesh();
}

void Area::generateNoteMesh() {
    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            std::vector<std::unique_ptr<Shape>> &shapes = note->getShapes();
        }
    }

    this->_noteMesh.setPrimitive(GL_TRIANGLES);

    this->_noteMesh.setUsage(GL_DYNAMIC_DRAW);
}

std::vector<std::unique_ptr<Lane>> &Area::getLanes() {
    return this->_lanes;
}

} // namespace component::game::singleplayer::play::area