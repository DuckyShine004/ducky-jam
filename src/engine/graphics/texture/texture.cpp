#include "engine/graphics/texture/texture.hpp"

#include "core/logger/logger_macros.hpp"

#include "external/stb/stb_image.h"
#include "external/stb/stb_image_write.h"

#include <glm/glm.hpp>

namespace engine::graphics::texture {

Texture::Texture(int id, int width, int height) : m_id(id), m_width(width), m_height(height), m_texture_id(0) {
    m_data.assign(width * height * default_channels, 0);
}

Texture::Texture(int id, Image &image) : m_id(id) {
    m_width = image.width();
    m_height = image.height();

    m_data = image.data();

    Region region{
        .width = image.width(),
        .height = image.height(),
        .source_width = image.source_width(),
        .source_height = image.source_height(),
        .uv = UV{},
    };

    m_regions.emplace(image.path(), region);
}

const Region &Texture::get_region(const std::filesystem::path &path) const {
    return m_regions.at(path);
}

void Texture::upload() {
    std::string tmp_path = ".tmp/texture-" + std::to_string(m_id) + ".png";

    int success = stbi_write_png(tmp_path.c_str(), m_width, m_height, default_channels, m_data.data(), m_width * default_channels);

    if (!success) {
        LOG_ERROR("Failed to write image to: {}", tmp_path);
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data.data());
}

int Texture::id() const {
    return m_id;
}

GLuint Texture::texture_id() const {
    return m_texture_id;
}

} // namespace engine::graphics::texture
