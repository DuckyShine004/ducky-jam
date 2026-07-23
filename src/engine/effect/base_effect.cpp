#include "engine/graphic/shader/shader_manager.hpp"

#include "engine/graphic/effect/base_effect.hpp"

using namespace engine::graphic::shader;

namespace engine::graphic::effect {

BaseEffect::BaseEffect(int shader_id) : Effect(shader_id) {
}

/**
 * @brief The default base effect.
 * @details Applies the base effect when no effect is specified. It applies no uniforms as
 * it only expects the base vertex attributes. Though it does apply the base shader.
 */
void BaseEffect::apply() const {
    ShaderManager::get_instance().use_shader(m_shader_id);
}

} // namespace engine::graphic::effect
