#pragma once

#include <memory>
#include <string>

#include "engine/graphic/effect/effect.hpp"
#include "engine/graphic/texture/uv.hpp"

#include "engine/graphic/drawable/drawable.hpp"

namespace engine::graphic::drawable {

class Sprite : public Drawable {
  public:
    Sprite(double x, double y, double width, double height, const std::string &texturePath, const std::string &effectName = "base");
    Sprite(double x, double y, double width, double height, const texture::UV &uv, const std::string &texturePath, const std::string &effectName = "base");
    Sprite(double x, double y, double width, double height, const std::string &texture_path, engine::graphic::effect::EffectPtr effect);
    Sprite(double x, double y, double width, double height, const texture::UV &uv, const std::string &texture_path, engine::graphic::effect::EffectPtr effect);

    void set_offset_x(double x);
    void set_offset_y(double y);

    void submit(engine::graphic::render::Renderer &renderer) const override;

    double x() const;
    double y() const;

    double offset_x() const;
    double offset_y() const;

    double width() const;
    double height() const;

    int texture_id() const;

    const engine::graphic::effect::EffectPtr &effect() const;

    const engine::graphic::texture::UV &uv() const;

    const std::string &texture_path() const;

  private:
    double m_x;
    double m_y;

    double m_offset_x;
    double m_offset_y;

    double m_width;
    double m_height;

    int m_texture_id;
    engine::graphic::effect::EffectPtr m_effect;

    engine::graphic::texture::UV m_uv;

    std::string m_texture_path;
};

} // namespace engine::graphic::drawable
