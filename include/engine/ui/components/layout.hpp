#pragma once

#include "core/structs/vector4.hpp"
#include "engine/ui/components/bloom.hpp"
#include "engine/ui/components/border.hpp"
#include "engine/ui/components/margin.hpp"
#include "engine/ui/components/padding.hpp"
#include "engine/ui/components/shadow.hpp"
#include "engine/ui/enums/align.hpp"

#include <cstdint>

namespace engine::ui::components {

struct Layout {
    static inline constexpr int max_width = 1 << 16;
    static inline constexpr int max_height = 1 << 16;

    float width = max_width;
    float height = max_height;

    Margin margin;
    Padding padding;

    enums::Align align = enums::Align::TopLeft;

    Border border;
    Shadow shadow;
    Bloom bloom;

    float opacity = 1.0f;

    core::structs::Vector4<std::uint8_t> colour;
};

} // namespace engine::ui::components
