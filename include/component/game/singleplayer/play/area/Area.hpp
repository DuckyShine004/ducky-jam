#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Note.hpp>

namespace component::game::singleplayer::play::area {

class Area final : public Component {
  public:
    Area();

    void create() override;

    void render() override;

  private:
    std::vector<std::unique_ptr<Note>> _notes;
};

} // namespace component::game::singleplayer::play::area