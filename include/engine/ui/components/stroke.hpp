#pragma once

#include <cstdint>

#include "core/structs/vector4.hpp"

namespace engine::ui::components {

struct Stroke {
    float width = 0.0f;

    core::structs::Vector4<std::uint8_t> colour;
};

} // namespace engine::ui::components
