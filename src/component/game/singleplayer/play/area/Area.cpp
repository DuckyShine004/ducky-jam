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
    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        lane->load();
    }
}

void Area::generateMesh() {
}

std::vector<std::unique_ptr<Lane>> &Area::getLanes() {
    return this->_lanes;
}

} // namespace component::game::singleplayer::play::area