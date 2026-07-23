#include "engine/graphic/shader/shader_manager.hpp"

#include "engine/graphic/effect/base_effect.hpp"
#include "engine/graphic/effect/effect_manager.hpp"

using namespace engine::graphic::shader;

namespace engine::graphic::effect {

EffectManager::EffectManager() = default;

EffectManager::~EffectManager() = default;

EffectManager &EffectManager::get_instance() {
    static EffectManager instance;

    return instance;
}

void EffectManager::initialise() {
    m_id = 0;

    ShaderManager &shader_manager = ShaderManager::get_instance();

    add_effect("base", std::make_unique<BaseEffect>(shader_manager.get_shader_id("base")));
}

int EffectManager::add_effect(const std::string &effect_name, std::unique_ptr<Effect> effect) {
    m_effect_references.emplace(effect_name, m_id);
    m_effects.emplace_back(std::move(effect));

    ++m_id;

    return m_id;
}

int EffectManager::get_effect_id(const std::string &name) const {
    return m_effect_references.at(name);
}

Effect &EffectManager::get_effect(int effect_id) const {
    return *m_effects.at(effect_id);
}

} // namespace engine::graphic::effect
