#include <cmath>
#include <stdexcept>

#include "external/stb/stb_image.h"
#include "external/stb/stb_image_resize2.h"

#include "engine/graphic/texture/image.hpp"

namespace engine::graphic::texture {

Image::Image(const std::string &path) : m_path(path) {
    int width;
    int height;
    int channels;

    unsigned char *image_data = stbi_load(path.c_str(), &width, &height, &channels, m_CHANNELS);

    if (!image_data) {
        throw std::runtime_error("ERROR: Could not load image: " + path);
    }

    // preserve aspect ratio
    double scale = 1.0f;

    scale = std::min(scale, static_cast<double>(m_MAX_WIDTH) / width);
    scale = std::min(scale, static_cast<double>(m_MAX_HEIGHT) / height);

    m_width = std::max(1, static_cast<int>(std::lround(width * scale)));
    m_height = std::max(1, static_cast<int>(std::lround(height * scale)));

    int size = m_width * m_height * m_CHANNELS;

    if (m_width == width && m_height == height) {
        m_data = std::vector<uint8_t>(image_data, image_data + size);
        stbi_image_free(image_data);
        return;
    }

    m_data.resize(size);

    if (!stbir_resize_uint8_linear(image_data, width, height, 0, m_data.data(), m_width, m_height, 0, STBIR_RGBA)) {
        stbi_image_free(image_data);
        throw std::runtime_error("ERROR: Could not resize image: " + path);
    };
}

int Image::width() const {
    return m_width;
}

int Image::height() const {
    return m_height;
}

const std::string &Image::path() const {
    return m_path;
}

const std::vector<std::uint8_t> &Image::data() const {
    return m_data;
}

} // namespace engine::graphic::texture
