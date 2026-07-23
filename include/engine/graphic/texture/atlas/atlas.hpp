#pragma once

#include <string>
#include <vector>

#include "external/glad/glad.h"

#include "engine/graphic/texture/image.hpp"
#include "engine/graphic/texture/texture.hpp"
#include "engine/graphic/texture/atlas/rectangle.hpp"

namespace engine::graphic::texture::atlas {

class Atlas final : public engine::graphic::texture::Texture {
  public:
    Atlas(int alias);

    static bool can_fit(int width, int height);
    bool can_add_texture(int width, int height);
    bool add_texture(const engine::graphic::texture::Image &image);

  private:
    int calculate_score(int width, int height, const engine::graphic::texture::atlas::Rectangle &rectangle);

    /**
     * @brief Best Short Side Fit (BSSF) heuristic.
     * @details Calculates the best short side fit score- minimises smaller leftover side.
     *
     * @param width The width of the image.
     * @param height The height of the image.
     * @param rectangle The rectangle which represents the area of the free space.
     */
    int best_short_side_fit(int width, int height);

    /**
     * @brief Best Area Fit (BAF) heuristic.
     * @details Calculates the best area fit score- minimises wasted area.
     *
     * @param width The width of the image.
     * @param height The height of the image.
     * @param rectangle The rectangle which represents the area of the free space.
     */
    int best_area_fit(int width, int height, const engine::graphic::texture::atlas::Rectangle &rectangle);

    void place_image(const std::vector<std::uint8_t> &image_data, int x, int y, int width, int height);

    bool intersect(const engine::graphic::texture::atlas::Rectangle &a, const engine::graphic::texture::atlas::Rectangle &b);
    void split_rectangle(const engine::graphic::texture::atlas::Rectangle &rectangle, const engine::graphic::texture::atlas::Rectangle &placed, std::vector<engine::graphic::texture::atlas::Rectangle> &rectangles);
    void split_left(const engine::graphic::texture::atlas::Rectangle &rectangle, const engine::graphic::texture::atlas::Rectangle &placed, std::vector<engine::graphic::texture::atlas::Rectangle> &rectangles);
    void split_right(const engine::graphic::texture::atlas::Rectangle &rectangle, const engine::graphic::texture::atlas::Rectangle &placed, std::vector<engine::graphic::texture::atlas::Rectangle> &rectangles);
    void split_top(const engine::graphic::texture::atlas::Rectangle &rectangle, const engine::graphic::texture::atlas::Rectangle &placed, std::vector<engine::graphic::texture::atlas::Rectangle> &rectangles);
    void split_bottom(const engine::graphic::texture::atlas::Rectangle &rectangle, const engine::graphic::texture::atlas::Rectangle &placed, std::vector<engine::graphic::texture::atlas::Rectangle> &rectangles);

    void create_uv(const std::string &path, const engine::graphic::texture::atlas::Rectangle &rectangle);

    static inline constexpr int m_MAX_WIDTH = 2048;
    static inline constexpr int m_MAX_HEIGHT = 2048;
    static inline constexpr int m_PADDING = 1;

    std::vector<engine::graphic::texture::atlas::Rectangle> m_rectangles;
};

} // namespace engine::graphic::texture::atlas
