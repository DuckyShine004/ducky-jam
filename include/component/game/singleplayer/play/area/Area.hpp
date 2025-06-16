#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Lane.hpp>

namespace component::game::singleplayer::play::area {

class Area final : public Component {
  public:
    Area();

    void create() override;

    void load() override;

    void update(float deltaTime) override;

    void generateMesh() override;

    void generateNoteMesh();

    Mesh &getNoteMesh();

    std::vector<std::unique_ptr<Lane>> &getLanes();

    glm::mat4 &getNoteModel();

  private:
    Mesh _noteMesh;

    std::vector<std::unique_ptr<Lane>> _lanes;

    glm::mat4 _noteModel;
};

} // namespace component::game::singleplayer::play::area