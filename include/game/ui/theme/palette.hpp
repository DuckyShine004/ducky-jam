#pragma once

#include <cstdint>

#include "core/structs/vector4.hpp"

namespace game::ui::theme {

struct Theme {
    core::structs::Vector4<std::uint8_t> background;
    core::structs::Vector4<std::uint8_t> topbar;
};

} // namespace game::ui::theme
