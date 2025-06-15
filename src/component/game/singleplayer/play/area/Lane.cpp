#include <component/game/singleplayer/play/area/Lane.hpp>

namespace component::game::singleplayer::play::area {

Lane::Lane() = default;

Lane::~Lane() = default;

void Lane::create() {
    std::unique_ptr<Note> note = std::make_unique<Note>();

    note->create();

    this->_notes.push_back(std::move(note));
}

void Lane::load() {
}

void Lane::generateMesh() {
}

std::vector<std::unique_ptr<Note>> &Lane::getNotes() {
    return this->_notes;
}

} // namespace component::game::singleplayer::play::area