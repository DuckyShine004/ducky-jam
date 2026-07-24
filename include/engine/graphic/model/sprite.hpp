#pragma once

#include <glm/glm.hpp>

#include <string>

#include "engine/graphic/texture/uv.hpp"

namespace engine::graphic::model {

class Sprite {
  public:
    Sprite(double x, double y, double width, double height, const std::string &texture_path, const std::string &effect_name = "base");
    Sprite(double x, double y, double width, double height, const engine::graphic::texture::UV &uv, const std::string &texture_path, const std::string &effect_name = "base");

    const glm::vec2 &position() const;

    double width() const;
    double height() const;

    int texture_id() const;
    int effect_id() const;

    const engine::graphic::texture::UV &uv() const;

    const std::string &texture_path() const;

  private:
    glm::vec2 m_position;

    double m_width;
    double m_height;

    int m_texture_id;
    int m_effect_id;

    engine::graphic::texture::UV m_uv;

    std::string m_texture_path;
};

} // namespace engine::graphic::model
