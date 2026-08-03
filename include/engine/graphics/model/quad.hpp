#pragma once

#include <cstdint>

#include "core/structs/vector4.hpp"

#include "engine/graphics/effect/effect.hpp"
#include "engine/graphics/texture/uv.hpp"

namespace engine::graphics::model {

struct Quad {
    float x;
    float y;
    float width;
    float height;

    int texture_id;

    engine::graphics::effect::EffectPtr effect;

    core::structs::Vector4<std::uint8_t> colour{255, 255, 255, 255};

    engine::graphics::texture::UV uv;
};

} // namespace engine::graphics::model
