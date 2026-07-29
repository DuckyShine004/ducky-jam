#include <stdexcept>
#include <utility>

#include "engine/graphic/shader/shader_manager.hpp"

#include "engine/graphic/effect/base_effect.hpp"
#include "engine/graphic/effect/effect_manager.hpp"

/* FIX: Fix this to cache custom effects */
using namespace engine::graphic::shader;

namespace engine::graphic::effect {

EffectManager::EffectManager() = default;

EffectManager::~EffectManager() = default;

EffectManager &EffectManager::get_instance() {
    static EffectManager instance;

    return instance;
}

void EffectManager::initialise() {
    ShaderManager &shader_manager = ShaderManager::get_instance();

    add_effect("base", std::make_shared<BaseEffect>(shader_manager.get_shader_id("base")));
}

void EffectManager::add_effect(const std::string &effect_name, EffectPtr effect) {
    if (!effect)
        throw std::invalid_argument("Cannot register a null effect");

    m_effects.insert_or_assign(effect_name, std::move(effect));
}

EffectPtr EffectManager::get_effect(const std::string &name) const {
    return m_effects.at(name);
}

} // namespace engine::graphic::effect
