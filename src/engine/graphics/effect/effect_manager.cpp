#include "engine/graphics/effect/effect_manager.hpp"

#include "engine/graphics/effect/base_effect.hpp"
#include "engine/graphics/effect/bloom_effect.hpp"
#include "engine/graphics/shader/shader_manager.hpp"

#include <stdexcept>
#include <utility>

/* FIX: Fix this to cache custom effects */
using namespace engine::graphics::shader;

namespace engine::graphics::effect {

EffectManager::EffectManager(ShaderManager &shader_manager) : m_shader_manager(shader_manager) {
    add_effect("base", std::make_shared<BaseEffect>(m_shader_manager.get_shader_id("base")));
}

void EffectManager::add_effect(const std::string &effect_name, EffectPtr effect) {
    if (!effect)
        throw std::invalid_argument("Cannot register a null effect");

    m_effects.insert_or_assign(effect_name, std::move(effect));
}

EffectPtr EffectManager::get_effect(const std::string &name) const {
    return m_effects.at(name);
}

EffectPtr EffectManager::get_bloom_effect(float intensity) {
    if (intensity <= 0.0f) {
        return get_effect("base");
    }

    auto iterator = m_bloom_effects.find(intensity);

    if (iterator != m_bloom_effects.end()) {
        return iterator->second;
    }

    const int shader_id = m_shader_manager.get_shader_id("base");
    EffectPtr effect = std::make_shared<BloomEffect>(shader_id, intensity);

    m_bloom_effects.emplace(intensity, effect);

    return effect;
}

} // namespace engine::graphics::effect
