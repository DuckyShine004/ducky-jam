#include "engine/graphic/effect/effect.hpp"

namespace engine::graphic::effect {

Effect::Effect(int shader_id) : m_shader_id(shader_id) {
}

int Effect::shader_id() const {
    return m_shader_id;
}

} // namespace engine::graphic::effect
