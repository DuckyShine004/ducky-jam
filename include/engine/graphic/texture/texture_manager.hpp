#pragma once

#include <array>
#include <string>

#include "engine/graphic/texture/texture_store.hpp"
#include "engine/graphic/texture/enums/texture_type.hpp"

namespace engine::graphic::texture {

class TextureManager {
  public:
    TextureManager(const TextureManager &) = delete;
    TextureManager &operator=(const TextureManager &) = delete;

    static TextureManager &get_instance();

    void initialise();
    void upload(const engine::graphic::texture::enums::TextureType &texture_type);

    void load_texture(const std::string &path, const engine::graphic::texture::enums::TextureType &texture_type);

    const engine::graphic::texture::Texture &get_texture(const std::string &path, const engine::graphic::texture::enums::TextureType &texture_type);

  private:
    TextureManager();
    ~TextureManager();

    engine::graphic::texture::TextureStore &resolve_texture_store(const engine::graphic::texture::enums::TextureType &texture_type);
    std::array<engine::graphic::texture::TextureStore, static_cast<std::size_t>(engine::graphic::texture::enums::TextureType::Count)> m_texture_stores;
};

} // namespace engine::graphic::texture
