#include "external/stb/stb_image.h"
#include "external/stb/stb_image_write.h"

#include "engine/graphic/texture/texture_manager.hpp"
#include "engine/graphic/texture/atlas/atlas.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine::graphic::texture::atlas;

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
    stbi_flip_vertically_on_write(true);

    m_id = 0;
}

void TextureManager::load_texture(const std::string &path) {
    LOG_INFO("Loading texture: {}", path);

    Image image(path);

    int width = image.width();
    int height = image.height();

    if (!Atlas::can_fit(width, height)) {
        m_textures.emplace_back(std::make_unique<Texture>(m_id, image));
        m_texture_references.emplace(path, m_id);
        ++m_id;
        return;
    }

    for (std::unique_ptr<Texture> &texture : m_textures) {
        Atlas *atlas = dynamic_cast<Atlas *>(texture.get());

        if (atlas == nullptr) {
            continue;
        }

        if (atlas->can_add_texture(width, height)) {
            atlas->add_texture(image);
            m_texture_references.emplace(path, atlas->id());
            return;
        }
    }

    std::unique_ptr<Texture> &texture = m_textures.emplace_back(std::make_unique<Atlas>(m_id));
    Atlas *atlas = dynamic_cast<Atlas *>(texture.get());

    atlas->add_texture(image);
    m_texture_references.emplace(path, m_id);
    ++m_id;
}

const Texture &TextureManager::get_texture(int id) const {
    return *m_textures[id].get();
}
const Texture &TextureManager::get_texture(const std::string &path) const {
    int id = m_texture_references.at(path);

    return *m_textures[id].get();
}

int TextureManager::get_texture_id(const std::string &path) {
    return m_texture_references.at(path);
}

void TextureManager::upload() {
    for (const std::unique_ptr<Texture> &texture : m_textures) {
        texture->upload();
    }
}

} // namespace engine::graphic::texture
