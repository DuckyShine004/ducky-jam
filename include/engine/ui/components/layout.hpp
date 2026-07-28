#pragma once

#include "core/structs/Vector4.hpp"

#include "engine/ui/components/margin.hpp"
#include "engine/ui/components/padding.hpp"
#include "engine/ui/components/border.hpp"

#include "engine/ui/enums/align.hpp"

namespace engine::ui::components {

struct Layout {
    float x = 0.0f;
    float y = 0.0f;

    float width = 0.0f;
    float height = 0.0f;

    Margin margin;
    Padding padding;

    enums::Align align = enums::Align::TopLeft;

    Border border;

    core::structs::Vector4<float> colour;
};

} // namespace engine::ui::components
