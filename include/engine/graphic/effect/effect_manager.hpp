#pragma once

#include <vector>
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
    int add_effect(const std::string &effect_name, std::unique_ptr<engine::graphic::effect::Effect> effect);

    int get_effect_id(const std::string &name) const;
    engine::graphic::effect::Effect &get_effect(int effect_id) const;

  private:
    EffectManager();
    ~EffectManager();

    int m_id;

    std::vector<std::unique_ptr<engine::graphic::effect::Effect>> m_effects;
    std::unordered_map<std::string, int> m_effect_references;
};

} // namespace engine::graphic::effect
