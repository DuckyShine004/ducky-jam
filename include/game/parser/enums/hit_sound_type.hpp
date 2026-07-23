#pragma once

#include <cstdint>

namespace game::parser::enums {

enum class HitSoundType : std::uint8_t {
    Normal = 1 << 0,
    Whistle = 1 << 1,
    Finish = 1 << 2,
    Clap = 1 << 3
};

} // namespace game::parser::enums
