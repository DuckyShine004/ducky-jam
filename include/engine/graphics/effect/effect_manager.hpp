#pragma once

#include <string>
#include <map>
#include <memory>
#include <unordered_map>

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::effect {

class EffectManager {
  public:
    EffectManager(const EffectManager &) = delete;
    EffectManager &operator=(const EffectManager &) = delete;

    static EffectManager &get_instance();

    void initialise();
    void add_effect(const std::string &effect_name, engine::graphics::effect::EffectPtr effect);

    engine::graphics::effect::EffectPtr get_effect(const std::string &name) const;
    engine::graphics::effect::EffectPtr get_bloom_effect(float intensity);

  private:
    EffectManager();
    ~EffectManager();

    std::unordered_map<std::string, engine::graphics::effect::EffectPtr> m_effects;
    std::map<float, engine::graphics::effect::EffectPtr> m_bloom_effects;
};

} // namespace engine::graphics::effect
