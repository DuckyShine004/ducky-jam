#pragma once

#include <memory>
#include <string>

#include "engine/graphics/effect/effect.hpp"
#include "engine/graphics/texture/uv.hpp"

#include "engine/graphics/drawable/drawable.hpp"

namespace engine::graphics::drawable {

class Sprite : public Drawable {
  public:
    Sprite(double x, double y, double width, double height, const std::string &texturePath, const std::string &effectName = "base");
    Sprite(double x, double y, double width, double height, const texture::UV &uv, const std::string &texturePath, const std::string &effectName = "base");
    Sprite(double x, double y, double width, double height, const std::string &texture_path, engine::graphics::effect::EffectPtr effect);
    Sprite(double x, double y, double width, double height, const texture::UV &uv, const std::string &texture_path, engine::graphics::effect::EffectPtr effect);

    void set_offset_x(double x);
    void set_offset_y(double y);

    void submit(engine::graphics::renderer::Renderer &renderer) const override;

    double x() const;
    double y() const;

    double offset_x() const;
    double offset_y() const;

    double width() const;
    double height() const;

    int texture_id() const;

    const engine::graphics::effect::EffectPtr &effect() const;

    const engine::graphics::texture::UV &uv() const;

    const std::string &texture_path() const;

  private:
    double m_x;
    double m_y;

    double m_offset_x;
    double m_offset_y;

    double m_width;
    double m_height;

    int m_texture_id;
    engine::graphics::effect::EffectPtr m_effect;

    engine::graphics::texture::UV m_uv;

    std::string m_texture_path;
};

} // namespace engine::graphics::drawable
