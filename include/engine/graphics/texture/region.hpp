#pragma once

#include "engine/graphics/texture/uv.hpp"

namespace engine::graphics::texture {

struct Region {
    int width;
    int height;
    int source_width;
    int source_height;

    engine::graphics::texture::UV uv;
};

} // namespace engine::graphics::texture
