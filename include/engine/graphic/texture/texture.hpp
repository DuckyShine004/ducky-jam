#pragma once

#include <glm/fwd.hpp>

#include <string>
#include <vector>
#include <cstdint>
#include <unordered_map>

#include "external/glad/glad.h"

#include "engine/graphic/texture/uv.hpp"
#include "engine/graphic/texture/image.hpp"
#include "engine/graphic/texture/enums/uv_type.hpp"

namespace engine::graphic::texture {

class Texture {
  public:
    Texture(int id, int width, int height);
    Texture(int id, engine::graphic::texture::Image &image);
    virtual ~Texture() = default;

    void upload();
    const engine::graphic::texture::UV &get_uv(const std::string &path) const;

    int id() const;
    GLuint texture_id() const;

  protected:
    static inline constexpr int m_CHANNELS = 4;

    int m_width;
    int m_height;

    GLuint m_texture_id;
    int m_id;

    std::vector<std::uint8_t> m_data;

    std::unordered_map<std::string, engine::graphic::texture::UV> m_uvs;
};

} // namespace engine::graphic::texture
