#include <stdexcept>

#include "external/stb/stb_image.h"

#include "engine/graphic/texture/texture_manager.hpp"
#include "engine/graphic/texture/atlas/atlas.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine::graphic::texture::atlas;
using namespace engine::graphic::texture::enums;

using namespace core::logger;

namespace engine::graphic::texture {

TextureManager::TextureManager() = default;

TextureManager::~TextureManager() = default;

TextureManager &TextureManager::get_instance() {
    static TextureManager instance;

    return instance;
}

void TextureManager::initialise() {
    stbi_set_flip_vertically_on_load(true);

    for (TextureStore &texture_store : m_texture_stores) {
        texture_store.id = 0;
    }
}

void TextureManager::load_texture(const std::string &path, const TextureType &texture_type) {
    LOG_INFO("Loading texture: {}", path);

    Image image(path);

    int width = image.width();
    int height = image.height();

    TextureStore &texture_store = resolve_texture_store(texture_type);

    if (!Atlas::can_fit(width, height)) {
        texture_store.textures.emplace_back(std::make_unique<Texture>(texture_store.id, image));
        texture_store.references.emplace(path, texture_store.id);
        ++texture_store.id;
        return;
    }

    for (std::unique_ptr<Texture> &texture : texture_store.textures) {
        Atlas *atlas = dynamic_cast<Atlas *>(texture.get());

        if (atlas != nullptr && atlas->can_add_texture(width, height)) {
            atlas->add_texture(image);
            texture_store.references.emplace(path, atlas->id());
            return;
        }
    }

    std::unique_ptr<Texture> &texture = texture_store.textures.emplace_back(std::make_unique<Atlas>(texture_store.id));

    Atlas *atlas = dynamic_cast<Atlas *>(texture.get());
    atlas->add_texture(image);
    texture_store.references.emplace(path, texture_store.id);
    ++texture_store.id;
}

const Texture &TextureManager::get_texture(const std::string &path, const TextureType &texture_type) {
    TextureStore &texture_store = resolve_texture_store(texture_type);

    int reference = texture_store.references[path];
    Texture *texture = texture_store.textures[reference].get();

    return *texture;
}

void TextureManager::upload(const TextureType &texture_type) {
    TextureStore &texture_store = resolve_texture_store(texture_type);

    for (const std::unique_ptr<Texture> &texture : texture_store.textures) {
        texture->upload();
    }
}

TextureStore &TextureManager::resolve_texture_store(const TextureType &texture_type) {
    std::size_t index = static_cast<std::size_t>(texture_type);

    if (index >= m_texture_stores.size()) {
        throw std::invalid_argument("Invalid texture type");
    }

    return m_texture_stores[index];
}

} // namespace engine::graphic::texture
