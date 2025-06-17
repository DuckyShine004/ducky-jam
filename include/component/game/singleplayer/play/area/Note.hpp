#pragma once

#include <component/Component.hpp>

namespace component::game::singleplayer::play::area {

class Note final : public Component {
  public:
    Note();

    void create() override;

    void update(float deltaTime) override;
};

} // namespace component::game::singleplayer::play::area