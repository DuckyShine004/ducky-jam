#pragma once

#include <component/Component.hpp>

#include <component/game/singleplayer/play/area/Lane.hpp>

#include "engine/sound/SoundSource.hpp"

#include <parser/beatmap/BeatmapParser.hpp>

using namespace engine::sound;

using namespace parser::beatmap;

namespace component::game::singleplayer::play::area {

class Area final : public Component {
  public:
    Area();

    void create() override;

    void update(float deltaTime) override;

    void load(const std::string &beatmapPath);

    void generateNoteMesh(SoundSource &source);

    Mesh &getNoteMesh();

    std::vector<std::unique_ptr<Lane>> &getLanes();

    glm::mat4 &getNoteModel();

  private:
    Mesh _noteMesh;

    BeatmapParser _beatmapParser;

    std::vector<std::unique_ptr<Lane>> _lanes;

    glm::mat4 _noteModel;

    int _notes;
};

} // namespace component::game::singleplayer::play::area