#pragma once

#include <engine/scene/Scene.hpp>

#include <engine/sound/SoundSource.hpp>

#include <component/game/singleplayer/play/area/Area.hpp>

using namespace engine::scene;

using namespace engine::sound;

using namespace component::game::singleplayer::play::area;

namespace application::game::singleplayer::play {

class Play final : public Scene {
  public:
    Play();

    void initialise() override;

    void create() override;

    void update(float deltaTime) override;

    void render() override;

    void load(const std::string &beatmapPath);

  private:
    static inline const char *_SHADER_NAMES[] = {
        "shaders/game/singleplayer/play/play",
    };

    Area _area;

    SoundSource _source;

    void renderNotes();
};

} // namespace application::game::singleplayer::play