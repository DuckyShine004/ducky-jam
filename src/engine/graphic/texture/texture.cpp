#include <glm/glm.hpp>
#include <stdexcept>

#include "external/stb/stb_image.h"
#include "external/stb/stb_image_write.h"

#include "engine/graphic/texture/texture.hpp"

#include "core/logger/logger_macros.hpp"

using namespace engine::graphic::texture::enums;

using namespace core::logger;

namespace engine::graphic::texture {

Texture::Texture(int id, int width, int height) : m_id(id), m_width(width), m_height(height) {
    m_data.assign(width * height * m_CHANNELS, 0);
}

Texture::Texture(int id, Image &image) : m_id(id) {
    m_width = image.width();
    m_height = image.height();

    m_data = image.data();

    UV uv{
        .u0 = 0.0f,
        .u1 = 1.0f,
        .v0 = 0.0f,
        .v1 = 1.0f,
    };

    m_uvs.emplace(image.path(), uv);
}

const UV &Texture::get_uv(const std::string &path) const {
    return m_uvs.at(path);
}

void Texture::upload() {
    std::string temp_path = "tmp/texture-" + std::to_string(m_id) + ".png";

    int success = stbi_write_png(temp_path.c_str(), m_width, m_height, m_CHANNELS, m_data.data(), m_width * m_CHANNELS);

    if (!success) {
        LOG_ERROR("Failed to write image");
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

} // namespace engine::graphic::texture
