#pragma once

#include "engine/graphic/texture/uv.hpp"

namespace engine::graphic::model {

// TODO: x0 and y0 should denote the BOTTOM LEFT corner of something, instead of anchoring by centre
// everything in duck jam is anchored bottom left
// This makes it so that resizing is consistent
class Quad {
  public:
    Quad(double x, double y, double width, double height, const engine::graphic::texture::UV &uv);

    void upload();
    void render();

  private:
    double m_x;
    double m_y;

    double m_width;
    double m_height;

    engine::graphic::texture::UV m_uv;
};

} // namespace engine::graphic::model
