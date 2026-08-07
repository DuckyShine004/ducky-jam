#include "engine/graphics/texture/texture_manager.hpp"

#include "core/logger/logger_macros.hpp"
#include "engine/graphics/texture/atlas/atlas.hpp"

#include "external/stb/stb_image.h"
#include "external/stb/stb_image_write.h"

namespace engine::graphics::texture {

using engine::graphics::texture::atlas::Atlas;

TextureManager::TextureManager() : m_id(0) {
    stbi_set_flip_vertically_on_load(true);
    stbi_flip_vertically_on_write(true);
}

void TextureManager::load_textures() {
    load_texture("resources/core/textures/colours/white.png");
}

void TextureManager::load_texture(const std::filesystem::path &path) {
    const std::filesystem::path texture_path = path.lexically_normal();

    if (m_texture_references.contains(texture_path)) {
        return;
    }

    LOG_INFO("Loading texture: {}", texture_path.string());

    Image image(texture_path);

    int width = image.width();
    int height = image.height();

    if (!Atlas::can_fit(width, height)) {
        m_textures.emplace_back(std::make_unique<Texture>(m_id, image));
        m_texture_references.emplace(texture_path, m_id);
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
            m_texture_references.emplace(texture_path, atlas->id());
            return;
        }
    }

    std::unique_ptr<Texture> &texture = m_textures.emplace_back(std::make_unique<Atlas>(m_id));
    Atlas *atlas = dynamic_cast<Atlas *>(texture.get());

    atlas->add_texture(image);
    m_texture_references.emplace(texture_path, m_id);
    ++m_id;
}

const Texture &TextureManager::get_texture(int id) const {
    return *m_textures.at(id);
}
const Texture &TextureManager::get_texture(const std::filesystem::path &path) const {
    int id = m_texture_references.at(path.lexically_normal());

    return *m_textures.at(id);
}

int TextureManager::get_texture_id(const std::filesystem::path &path) const {
    return m_texture_references.at(path.lexically_normal());
}

void TextureManager::upload() {
    for (const std::unique_ptr<Texture> &texture : m_textures) {
        texture->upload();
    }
}

} // namespace engine::graphics::texture
