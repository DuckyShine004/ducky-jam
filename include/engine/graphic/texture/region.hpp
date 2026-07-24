#pragma once

#include "engine/graphic/texture/uv.hpp"

namespace engine::graphic::texture {

struct Region {
    int width;
    int height;
    int source_width;
    int source_height;

    engine::graphic::texture::UV uv;
};

} // namespace engine::graphic::texture
