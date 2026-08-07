#include "engine/graphics/drawable/sprite.hpp"

#include "engine/graphics/renderer/renderer.hpp"

#include <utility>

namespace engine::graphics::drawable {

Sprite::Sprite(double x, double y, double width, double height, const std::filesystem::path &texture_path, effect::EffectPtr effect) : Sprite(x, y, width, height, texture::UV{}, texture_path, std::move(effect)) {
}

Sprite::Sprite(double x, double y, double width, double height, const texture::UV &uv, const std::filesystem::path &texture_path, effect::EffectPtr effect)
    : m_x(x), m_y(y), m_offset_x(0.0f), m_offset_y(0.0f), m_width(width), m_height(height), m_effect(std::move(effect)), m_uv(uv), m_texture_path(texture_path) {
}

void Sprite::submit(renderer::Renderer &renderer) const {
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

const effect::EffectPtr &Sprite::effect() const {
    return m_effect;
}

const texture::UV &Sprite::uv() const {
    return m_uv;
}

const std::filesystem::path &Sprite::texture_path() const {
    return m_texture_path;
}

} // namespace engine::graphics::drawable
