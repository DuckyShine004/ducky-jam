#include "engine/graphic/model/sprite.hpp"

#include "engine/graphic/effect/effect_manager.hpp"

#include "engine/graphic/texture/texture_manager.hpp"

using namespace engine::graphic::effect;
using namespace engine::graphic::texture;

namespace engine::graphic::model {

Sprite::Sprite(double x, double y, double width, double height, const std::string &texture_path, const std::string &effect_name) : m_position(x, y), m_width(width), m_height(height), m_texture_path(texture_path) {
    m_texture_id = TextureManager::get_instance().get_texture_id(texture_path);
    m_effect_id = EffectManager::get_instance().get_effect_id(effect_name);
}

const glm::vec2 &Sprite::position() const {
    return m_position;
}

double Sprite::width() const {
    return m_width;
}

double Sprite::height() const {
    return m_height;
}

int Sprite::texture_id() const {
    return m_texture_id;
}

int Sprite::effect_id() const {
    return m_effect_id;
}

const std::string &Sprite::texture_path() const {
    return m_texture_path;
}

} // namespace engine::graphic::model
