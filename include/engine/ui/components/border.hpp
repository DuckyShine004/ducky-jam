#pragma once

#include "engine/ui/components/stroke.hpp"

namespace engine::ui::components {

struct Border {
    float radius = 0.0f;

    Stroke left;
    Stroke right;
    Stroke top;
    Stroke bottom;
};

} // namespace engine::ui::components
