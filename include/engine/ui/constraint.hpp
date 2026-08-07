#pragma once

#include "core/structs/vector2.hpp"

namespace engine::ui {

struct Constraint {
    core::structs::Vector2<float> minimum;
    core::structs::Vector2<float> maximum;
};

} // namespace engine::ui
