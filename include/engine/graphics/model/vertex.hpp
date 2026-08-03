#pragma once

#include <glm/glm.hpp>

#include "core/structs/vector4.hpp"

namespace engine::graphics::model {

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;
    std::uint32_t colour = 0xFFFFFFFF;

    Vertex(float x, float y, float u, float v, const core::structs::Vector4<std::uint8_t> &colour = {255, 255, 255, 255}) : position{x, y}, uv{u, v}, colour{pack_colour(colour)} {
    }

    static inline constexpr std::uint32_t pack_colour(const core::structs::Vector4<std::uint8_t> &colour) {
        return colour.r | (colour.g << 8) | (colour.b << 16) | (colour.a << 24);
    }
};

} // namespace engine::graphics::model
