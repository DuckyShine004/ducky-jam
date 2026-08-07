#pragma once

#include "engine/graphics/texture/image.hpp"
#include "engine/graphics/texture/region.hpp"

#include "external/glad/glad.h"

#include <cstdint>
#include <filesystem>
#include <glm/fwd.hpp>
#include <unordered_map>
#include <vector>

namespace engine::graphics::texture {

class Texture {
  public:
    Texture(int id, int width, int height);
    Texture(int id, engine::graphics::texture::Image &image);
    virtual ~Texture() = default;

    void upload();
    const engine::graphics::texture::Region &get_region(const std::filesystem::path &path) const;

    int id() const;
    GLuint texture_id() const;

  protected:
    static inline constexpr int default_channels = 4;

    int m_width;
    int m_height;

    int m_id;

    GLuint m_texture_id;

    std::vector<std::uint8_t> m_data;

    std::unordered_map<std::filesystem::path, engine::graphics::texture::Region> m_regions;
};

} // namespace engine::graphics::texture
