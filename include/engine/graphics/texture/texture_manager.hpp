#pragma once

#include "engine/graphics/texture/texture.hpp"

#include <filesystem>
#include <memory>
#include <unordered_map>
#include <vector>

namespace engine::graphics::texture {

class TextureManager {
  public:
    TextureManager();

    void load_textures();

    void upload();
    void load_texture(const std::filesystem::path &path);

    const engine::graphics::texture::Texture &get_texture(int id) const;
    const engine::graphics::texture::Texture &get_texture(const std::filesystem::path &path) const;

    int get_texture_id(const std::filesystem::path &path) const;

  private:
    int m_id;

    std::vector<std::unique_ptr<engine::graphics::texture::Texture>> m_textures;
    std::unordered_map<std::filesystem::path, int> m_texture_references;
};

} // namespace engine::graphics::texture
