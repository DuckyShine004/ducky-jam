#pragma once

#include "engine/graphics/texture/atlas/rectangle.hpp"
#include "engine/graphics/texture/image.hpp"
#include "engine/graphics/texture/texture.hpp"

#include "external/glad/glad.h"

#include <vector>

namespace engine::graphics::texture::atlas {

class Atlas final : public engine::graphics::texture::Texture {
  public:
    Atlas(int alias);

    static bool can_fit(int width, int height);
    bool can_add_texture(int width, int height);
    bool add_texture(const engine::graphics::texture::Image &image);

  private:
    static inline constexpr int max_width = 2048;
    static inline constexpr int max_height = 2048;
    static inline constexpr int padding = 1;

    std::vector<engine::graphics::texture::atlas::Rectangle> m_rectangles;

    int calculate_score(int width, int height, const engine::graphics::texture::atlas::Rectangle &rectangle);

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
    int best_area_fit(int width, int height, const engine::graphics::texture::atlas::Rectangle &rectangle);

    void place_image(const std::vector<std::uint8_t> &image_data, int x, int y, int width, int height);

    bool intersect(const engine::graphics::texture::atlas::Rectangle &a, const engine::graphics::texture::atlas::Rectangle &b);
    void split_rectangle(const engine::graphics::texture::atlas::Rectangle &rectangle, const engine::graphics::texture::atlas::Rectangle &placed, std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);
    void split_left(const engine::graphics::texture::atlas::Rectangle &rectangle, const engine::graphics::texture::atlas::Rectangle &placed, std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);
    void split_right(const engine::graphics::texture::atlas::Rectangle &rectangle, const engine::graphics::texture::atlas::Rectangle &placed, std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);
    void split_top(const engine::graphics::texture::atlas::Rectangle &rectangle, const engine::graphics::texture::atlas::Rectangle &placed, std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);
    void split_bottom(const engine::graphics::texture::atlas::Rectangle &rectangle, const engine::graphics::texture::atlas::Rectangle &placed, std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);

    void prune(const std::vector<engine::graphics::texture::atlas::Rectangle> &rectangles);

    void create_region(const engine::graphics::texture::Image &image, const engine::graphics::texture::atlas::Rectangle &rectangle);
};

} // namespace engine::graphics::texture::atlas
