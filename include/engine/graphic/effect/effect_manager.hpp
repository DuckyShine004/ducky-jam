#pragma once

#include <string>
#include <memory>
#include <unordered_map>

#include "engine/graphic/effect/effect.hpp"

namespace engine::graphic::effect {

class EffectManager {
  public:
    EffectManager(const EffectManager &) = delete;
    EffectManager &operator=(const EffectManager &) = delete;

    static EffectManager &get_instance();

    void initialise();
    void add_effect(const std::string &effect_name, engine::graphic::effect::EffectPtr effect);

    engine::graphic::effect::EffectPtr get_effect(const std::string &name) const;

  private:
    EffectManager();
    ~EffectManager();

    std::unordered_map<std::string, engine::graphic::effect::EffectPtr> m_effects;
};

} // namespace engine::graphic::effect
