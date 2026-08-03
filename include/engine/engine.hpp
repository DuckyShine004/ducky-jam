#pragma once

#include <GLFW/glfw3.h>

#include <optional>

#include "engine/graphics/renderer/renderer.hpp"
#include "engine/scene/scene.hpp"
#include "engine/audio/audio_clock.hpp"

#include "game/parser/beatmap.hpp"
#include "game/gameplay/stage/stage.hpp"
#include "game/skinning/config/skin_config.hpp"

namespace engine {

class Engine {
  public:
    Engine();

    void initialise(int framebuffer_width, int framebuffer_height);
    void resize(int framebuffer_width, int framebuffer_height);
    void shutdown();
    void update(GLFWwindow *window, double delta_time);
    void render();

  private:
    double m_time;

    std::optional<engine::audio::AudioClock> m_audio_clock;

    engine::graphics::renderer::Renderer m_renderer;

    game::parser::Beatmap m_beatmap;
    game::skinning::config::SkinConfig m_skin_config;
    std::optional<game::gameplay::stage::Stage> m_stage;

    std::unique_ptr<engine::scene::Scene> m_scene;
};

} // namespace engine
