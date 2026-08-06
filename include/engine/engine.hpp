#pragma once

#include "engine/audio/audio_manager.hpp"
#include "engine/graphics/effect/effect_manager.hpp"
#include "engine/graphics/renderer/renderer.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"
#include "engine/scene/scene.hpp"
#include "game/parser/importer.hpp"

#include <GLFW/glfw3.h>

namespace engine {

class Engine {
  public:
    Engine(int width, int height);
    ~Engine();

    Engine(const Engine &other) = delete;
    Engine &operator=(const Engine &other) = delete;
    Engine(Engine &&other) = delete;
    Engine &operator=(Engine &&other) = delete;

    void resize(int framebuffer_width, int framebuffer_height);
    void drop(const std::vector<std::string> &paths);
    void update(double delta_time);
    void render();

  private:
    double m_time;

    // std::optional<engine::audio::AudioClock> m_audio_clock;

    // managers
    engine::audio::AudioManager m_audio_manager;

    engine::graphics::shader::ShaderManager m_shader_manager;
    engine::graphics::texture::TextureManager m_texture_manager;
    engine::graphics::effect::EffectManager m_effect_manager;

    engine::graphics::renderer::Renderer m_renderer;

    // game::parser::Beatmap m_beatmap;
    // game::skinning::config::SkinConfig m_skin_config;
    // std::optional<game::gameplay::stage::Stage> m_stage;

    std::unique_ptr<engine::scene::Scene> m_scene;

    game::parser::Importer m_importer;
};

} // namespace engine
