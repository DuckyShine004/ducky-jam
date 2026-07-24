#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace engine::graphic::texture {

class Image {
  public:
    Image(const std::string &path);

    int width() const;
    int height() const;
    int source_width() const;
    int source_height() const;

    const std::string &path() const;

    const std::vector<std::uint8_t> &data() const;

  private:
    static inline constexpr int m_CHANNELS = 4;

    static inline constexpr int m_MAX_WIDTH = (1 << 13);
    static inline constexpr int m_MAX_HEIGHT = (1 << 13);

    int m_width;
    int m_height;
    int m_source_width;
    int m_source_height;

    std::string m_path;

    std::vector<std::uint8_t> m_data;
};

} // namespace engine::graphic::texture
