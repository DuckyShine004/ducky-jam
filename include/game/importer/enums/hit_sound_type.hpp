#pragma once

#include <cstdint>

namespace game::importer::enums {

enum class HitSoundType : std::uint8_t {
    Normal = 1 << 0,
    Whistle = 1 << 1,
    Finish = 1 << 2,
    Clap = 1 << 3
};

} // namespace game::importer::enums
