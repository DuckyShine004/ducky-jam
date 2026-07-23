#pragma once

#include <cstddef>

namespace engine::graphic::texture::enums {

// TODO: Should only really be two texture types, player skin (can change), and UI (defined by me which cannot change during playtime)
enum class TextureType : std::size_t {
    Skin,
    Core,
    Count,
};

} // namespace engine::graphic::texture::enums
