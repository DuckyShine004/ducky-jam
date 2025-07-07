#define STB_IMAGE_IMPLEMENTATION

#include "engine/texture/Image.hpp"

#include <filesystem>

namespace engine::texture {

Image::Image(const std::string &imagePath) {
    std::filesystem::path fullPath(imagePath);

    stbi_set_flip_vertically_on_load(true);

    this->_buffer = stbi_load(fullPath.c_str(), &this->_width, &this->_height, &this->_channels, 0);
}

unsigned char *Image::getBuffer() {
    return this->_buffer;
}

void Image::clearBuffer() {
    stbi_image_free(this->_buffer);
}

} // namespace engine::texture