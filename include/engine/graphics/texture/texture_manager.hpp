#pragma once

#include "engine/graphics/texture/texture.hpp"

#include <memory>
#include <string>
#include <vector>

namespace engine::graphics::texture {

class TextureManager {
  public:
    TextureManager();

    void initialise();
    void upload();
    void load_texture(const std::string &path);

    const engine::graphics::texture::Texture &get_texture(int id) const;
    const engine::graphics::texture::Texture &get_texture(const std::string &path) const;

    int get_texture_id(const std::string &path);

  private:
    int m_id;

    std::vector<std::unique_ptr<engine::graphics::texture::Texture>> m_textures;

    std::unordered_map<std::string, int> m_texture_references;
};

} // namespace engine::graphics::texture
