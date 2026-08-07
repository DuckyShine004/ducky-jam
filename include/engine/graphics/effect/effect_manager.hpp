#pragma once

#include "engine/graphics/effect/effect.hpp"
#include "engine/graphics/shader/shader_manager.hpp"

#include <map>
#include <string>
#include <unordered_map>

namespace engine::graphics::effect {

class EffectManager {
  public:
    EffectManager(engine::graphics::shader::ShaderManager &shader_manager);

    void load_effects();

    void add_effect(const std::string &effect_name, engine::graphics::effect::EffectPtr effect);

    engine::graphics::effect::EffectPtr get_effect(const std::string &name) const;
    engine::graphics::effect::EffectPtr get_bloom_effect(float intensity);

  private:
    engine::graphics::shader::ShaderManager &m_shader_manager;

    std::unordered_map<std::string, engine::graphics::effect::EffectPtr> m_effects;
    std::map<float, engine::graphics::effect::EffectPtr> m_bloom_effects;
};

} // namespace engine::graphics::effect
