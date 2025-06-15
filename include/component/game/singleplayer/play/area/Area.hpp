#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Lane.hpp>

namespace component::game::singleplayer::play::area {

class Area final : public Component {
  public:
    Area();

    void create() override;

    std::vector<std::unique_ptr<Lane>> &getLanes();

  private:
    std::vector<std::unique_ptr<Lane>> _lanes;
};

} // namespace component::game::singleplayer::play::area