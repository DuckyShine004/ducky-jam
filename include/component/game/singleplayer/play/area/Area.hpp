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

    void initialise(const std::string &beatmapPath);

    void create() override;

    void update(float deltaTime) override;

    void load();

    void generateNoteMesh(SoundSource &source);

    int getNumberOfRenderedNotes();

    Mesh &getNoteMesh();

    std::vector<std::unique_ptr<Lane>> &getLanes();

  private:
    Mesh _noteMesh;

    BeatmapParser _beatmapParser;

    std::vector<std::unique_ptr<Lane>> _lanes;

    int _notes;

    int _numberOfRenderedNotes;

    void calculateNotePosition(std::unique_ptr<Note> &note, float position);

    bool isNoteInBound(std::unique_ptr<Note> &note);

    glm::vec3 getNoteColour(int laneIndex);
};

} // namespace component::game::singleplayer::play::area