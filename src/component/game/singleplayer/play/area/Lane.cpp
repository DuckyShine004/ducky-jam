#include <component/game/singleplayer/play/area/Lane.hpp>

namespace component::game::singleplayer::play::area {

Lane::Lane() = default;

Lane::~Lane() = default;

void Lane::update(float deltaTime) {
    for (std::unique_ptr<Note> &note : this->_notes) {
        note->update(deltaTime);
    }
}

void Lane::addNote(std::unique_ptr<Note> note) {
    this->_notes.push_back(std::move(note));
}

std::vector<std::unique_ptr<Note>> &Lane::getNotes() {
    return this->_notes;
}

} // namespace component::game::singleplayer::play::area