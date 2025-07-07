#pragma once

#include <string>
#include <vector>

#include <stb/stb_image.h>

// Filepath
namespace engine::texture {

class Image {
  public:
    Image(const std::string &imagePath);

    unsigned char *getBuffer();

    void clearBuffer();

  private:
    int _width;
    int _height;
    int _channels;

    unsigned char *_buffer;
};

} // namespace engine::texture