#pragma once

#include <cstdint>

#include "core/structs/vector4.hpp"

#include "engine/graphic/texture/uv.hpp"

namespace engine::graphic::model {

struct Quad {
    float x;
    float y;
    float width;
    float height;

    int texture_id;
    int effect_id;

    core::structs::Vector4<std::uint8_t> colour{255, 255, 255, 255};

    engine::graphic::texture::UV uv;
};

} // namespace engine::graphic::model
