#pragma once

#include <GLFW/glfw3.h>

#include <optional>

#include "engine/graphic/render/renderer.hpp"
#include "engine/scene/scene.hpp"
#include "engine/audio/audio_clock.hpp"

#include "game/parser/beatmap.hpp"
#include "game/gameplay/stage/stage.hpp"
#include "game/skinning/config/skin_config.hpp"

namespace engine {

class Engine {
  public:
    Engine();

    void initialise();
    void update(GLFWwindow *window, double delta_time);
    void render();

  private:
    double m_time;

    std::optional<engine::audio::AudioClock> m_audio_clock;

    engine::graphic::render::Renderer m_renderer;

    game::parser::Beatmap m_beatmap;
    game::skinning::config::SkinConfig m_skin_config;
    std::optional<game::gameplay::stage::Stage> m_stage;

    std::unique_ptr<engine::scene::Scene> m_scene;
};

} // namespace engine
