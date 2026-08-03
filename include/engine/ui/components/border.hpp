#pragma once

#include "engine/ui/components/stroke.hpp"

namespace engine::ui::components {

struct Border {
    core::structs::Vector4<float> radius{};

    Stroke left;
    Stroke right;
    Stroke top;
    Stroke bottom;
};

} // namespace engine::ui::components
