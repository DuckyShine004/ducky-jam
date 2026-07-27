#pragma once

#include "core/structs/Vector4.hpp"

namespace engine::ui::components {

struct Stroke {
    float width = 0.0f;

    core::structs::Vector4<float> colour;
};

} // namespace engine::ui::components
