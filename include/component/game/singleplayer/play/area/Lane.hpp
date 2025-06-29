#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Note.hpp>

namespace component::game::singleplayer::play::area {

class Lane final : public Component {
  public:
    Lane();

    virtual ~Lane();

    void update(float deltaTime) override;

    void addNote(std::unique_ptr<Note> note);

    std::vector<std::unique_ptr<Note>> &getNotes();

  private:
    std::vector<std::unique_ptr<Note>> _notes;
};

} // namespace component::game::singleplayer::play::area