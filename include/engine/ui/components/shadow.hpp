#pragma once

#include <cstdint>

#include "core/structs/vector4.hpp"

namespace engine::ui::components {

struct Shadow {
    float offset_x = 0.0f;
    float offset_y = 0.0f;
    float blur_radius = 0.0f;
    float spread_radius = 0.0f;

    core::structs::Vector4<std::uint8_t> colour;
};

} // namespace engine::ui::components
