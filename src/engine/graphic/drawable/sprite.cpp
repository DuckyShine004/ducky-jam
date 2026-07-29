#include <utility>

#include "engine/graphic/render/renderer.hpp"

#include "engine/graphic/drawable/sprite.hpp"

#include "engine/graphic/effect/effect_manager.hpp"

#include "engine/graphic/texture/texture_manager.hpp"

using namespace engine::graphic::effect;
using namespace engine::graphic::render;
using namespace engine::graphic::texture;

namespace engine::graphic::drawable {

Sprite::Sprite(double x, double y, double width, double height, const std::string &texturePath, const std::string &effectName) : Sprite(x, y, width, height, UV{}, texturePath, effectName) {
}

Sprite::Sprite(double x, double y, double width, double height, const UV &uv, const std::string &texture_path, const std::string &effect_name)
    : Sprite(x, y, width, height, uv, texture_path, EffectManager::get_instance().get_effect(effect_name)) {
}

Sprite::Sprite(double x, double y, double width, double height, const std::string &texture_path, EffectPtr effect)
    : Sprite(x, y, width, height, UV{}, texture_path, std::move(effect)) {
}

Sprite::Sprite(double x, double y, double width, double height, const UV &uv, const std::string &texture_path, EffectPtr effect)
    : m_x(x),
      m_y(y),
      m_offset_x(0.0f),
      m_offset_y(0.0f),
      m_width(width),
      m_height(height),
      m_effect(std::move(effect)),
      m_uv(uv),
      m_texture_path(texture_path) {
    m_texture_id = TextureManager::get_instance().get_texture_id(texture_path);
}

void Sprite::submit(Renderer &renderer) const {
    renderer.queue(*this);
}

void Sprite::set_offset_x(double offset_x) {
    m_offset_x = offset_x;
}

void Sprite::set_offset_y(double offset_y) {
    m_offset_y = offset_y;
}

double Sprite::x() const {
    return m_x;
}

double Sprite::y() const {
    return m_y;
}

double Sprite::offset_x() const {
    return m_offset_x;
}

double Sprite::offset_y() const {
    return m_offset_y;
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

const EffectPtr &Sprite::effect() const {
    return m_effect;
}

const UV &Sprite::uv() const {
    return m_uv;
}

const std::string &Sprite::texture_path() const {
    return m_texture_path;
}

} // namespace engine::graphic::drawable
