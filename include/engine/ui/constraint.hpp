#pragma once

#include "core/structs/vector2.hpp"

using namespace core::structs;

namespace engine::ui {

struct Constraint {
    Vector2<float> minimum;
    Vector2<float> maximum;
};

} // namespace engine::ui
