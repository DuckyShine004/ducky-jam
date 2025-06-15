#pragma once

#include <component/Component.hpp>

namespace component::game::singleplayer::play::area {

class Note final : Component {
  public:
    Note();

    void create() override;

    void load() override;

    void generateMesh() override;
};

} // namespace component::game::singleplayer::play::area