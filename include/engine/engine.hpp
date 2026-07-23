
#pragma once

#include <GLFW/glfw3.h>

#include <optional>

#include "game/parser/beatmap.hpp"
#include "game/skinning/config/skin_config.hpp"

#include "engine/graphic/render/renderer.hpp"
#include "engine/sound/sound_clock.hpp"

namespace engine {

class Engine {
  public:
    Engine();

    void initialise();
    void update(GLFWwindow *window, double delta_time);
    void render();

  private:
    double m_time;
    unsigned int m_note_head_texture_id = 0;

    std::optional<engine::sound::SoundClock> m_sound_clock;

    engine::graphic::render::Renderer m_renderer;

    game::parser::Beatmap m_beatmap;
    game::skinning::config::SkinConfig m_skin_config;
};

} // namespace engine
