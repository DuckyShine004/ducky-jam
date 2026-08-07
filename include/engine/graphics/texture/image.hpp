#pragma once

#include <cstdint>
#include <filesystem>
#include <vector>

namespace engine::graphics::texture {

class Image {
  public:
    explicit Image(const std::filesystem::path &path);

    int width() const;
    int height() const;
    int source_width() const;
    int source_height() const;

    const std::filesystem::path &path() const;

    const std::vector<std::uint8_t> &data() const;

  private:
    static inline constexpr int default_channels = 4;

    static inline constexpr int max_width = (1 << 13);
    static inline constexpr int max_height = (1 << 13);

    int m_width;
    int m_height;
    int m_source_width;
    int m_source_height;

    std::filesystem::path m_path;

    std::vector<std::uint8_t> m_data;
};

} // namespace engine::graphics::texture
