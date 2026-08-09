#pragma once

#include "engine/audio/audio_pool.hpp"
#include "engine/graphics/effect/effect_manager.hpp"
#include "engine/graphics/renderer/renderer.hpp"
#include "engine/graphics/shader/shader_manager.hpp"
#include "engine/graphics/texture/texture_manager.hpp"

// NOTE: Could be better design, idk acts as service locator for now
namespace engine {

struct EngineServices {
    audio::AudioPool &audio_pool;

    graphics::texture::TextureManager &texture_manager;
    graphics::shader::ShaderManager &shader_manager;
    graphics::effect::EffectManager &effect_manager;

    graphics::renderer::Renderer &renderer;
};

class Engine {
  public:
    Engine(int width, int height);

    void load();
    void resize_framebuffer(int width, int height);

    EngineServices services();

  private:
    engine::audio::AudioPool m_audio_pool;
    engine::graphics::shader::ShaderManager m_shader_manager;
    engine::graphics::texture::TextureManager m_texture_manager;
    engine::graphics::effect::EffectManager m_effect_manager;
    engine::graphics::renderer::Renderer m_renderer;
};

} // namespace engine
