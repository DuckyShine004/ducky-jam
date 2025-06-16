#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Lane.hpp>

namespace component::game::singleplayer::play::area {

class Area final : public Component {
  public:
    Area();

    void create() override;

    void load() override;

    void generateMesh() override;

    void generateNoteMesh();

    std::vector<std::unique_ptr<Lane>> &getLanes();

    Mesh &getNoteMesh();

  private:
    std::vector<std::unique_ptr<Lane>> _lanes;

    Mesh _noteMesh;
};

} // namespace component::game::singleplayer::play::area