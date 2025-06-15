#pragma once

#include <engine/scene/Scene.hpp>

using namespace engine::scene;

namespace application::game::singleplayer::play {

class Play final : public Scene {
  public:
    Play();

    void initialise() override;

    void create() override;

    void update(float deltaTime) override;

    void render() override;

  private:
    static inline const char *_SHADER_NAMES[] = {
        "shaders/game/singleplayer/play/play",
    };
};

} // namespace application::game::singleplayer::play