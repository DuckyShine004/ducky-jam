#pragma once

#include <engine/scene/Scene.hpp>

#include <component/game/singleplayer/play/area/Area.hpp>

using namespace engine::scene;

using namespace component::game::singleplayer::play::area;

namespace application::game::singleplayer::play {

class Play final : public Scene {
  public:
    Play();

    void initialise() override;

    void create() override;

    void load() override;

    void update(float deltaTime) override;

    void render() override;

  private:
    static inline const char *_SHADER_NAMES[] = {
        "shaders/game/singleplayer/play/play",
    };

    Area _area;

    void renderNotes();
};

} // namespace application::game::singleplayer::play