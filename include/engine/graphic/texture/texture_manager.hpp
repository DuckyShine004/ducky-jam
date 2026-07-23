#pragma once

#include <vector>
#include <string>
#include <memory>

#include "engine/graphic/texture/texture.hpp"

namespace engine::graphic::texture {

class TextureManager {
  public:
    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;

    static TextureManager &get_instance();

    void initialise();
    void upload();
    void load_texture(const std::string &path);

    const engine::graphic::texture::Texture &get_texture(int id) const;
    const engine::graphic::texture::Texture &get_texture(const std::string &path) const;

    int get_texture_id(const std::string &path);

  private:
    TextureManager();
    ~TextureManager();

    int m_id;

    std::vector<std::unique_ptr<engine::graphic::texture::Texture>> m_textures;

    std::unordered_map<std::string, int> m_texture_references;
};

} // namespace engine::graphic::texture
