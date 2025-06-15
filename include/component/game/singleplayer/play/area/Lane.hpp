#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Note.hpp>

namespace component::game::singleplayer::play::area {

class Lane final : public Component {
  public:
    Lane();

    virtual ~Lane();

    void create() override;

    void load() override;

    void generateMesh() override;

    std::vector<std::unique_ptr<Note>> &getNotes();

  private:
    std::vector<std::unique_ptr<Note>> _notes;
};

} // namespace component::game::singleplayer::play::area