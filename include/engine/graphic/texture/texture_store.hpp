#pragma once

#include <memory>

#include "engine/graphic/texture/texture.hpp"

namespace engine::graphic::texture {

struct TextureStore {
    int id;
    std::vector<std::unique_ptr<engine::graphic::texture::Texture>> textures;
    std::unordered_map<std::string, int> references;
};

} // namespace engine::graphic::texture
