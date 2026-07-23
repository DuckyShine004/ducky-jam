#include "external/stb/stb_image.h"
#include "external/stb/stb_image_write.h"

#include "engine/graphic/texture/atlas/atlas.hpp"
#include "engine/graphic/texture/atlas/rectangle.hpp"

#include "core/logger/logger_macros.hpp"

namespace engine::graphic::texture::atlas {

using engine::graphic::texture::atlas::Rectangle;

Atlas::Atlas(int id) : Texture(id, m_MAX_WIDTH, m_MAX_HEIGHT) {
    m_rectangles.emplace_back(m_PADDING, m_PADDING, m_MAX_WIDTH - (m_PADDING << 1), m_MAX_HEIGHT - (m_PADDING << 1));
}

bool Atlas::can_fit(int width, int height) {
    int dw = width + (m_PADDING << 1);
    int dh = height + (m_PADDING << 1);

    return dw <= m_MAX_WIDTH && dh <= m_MAX_HEIGHT;
}

bool Atlas::add_texture(const Image &image) {
    int width = image.width();
    int height = image.height();

    // fit the image into a free rectangle based on max rect algorithm
    int best_score = m_MAX_WIDTH * m_MAX_HEIGHT;
    Rectangle best_rectangle;

    for (const Rectangle &rectangle : m_rectangles) {
        if (width > rectangle.width || height > rectangle.height) {
            continue;
        }

        int score = calculate_score(width, height, rectangle);

        if (score < best_score) {
            best_score = score;
            best_rectangle = rectangle;
        }
    }

    // place image inside rectangle
    place_image(image.data(), best_rectangle.x, best_rectangle.y, width, height);

    // Use this if it doesn't work
    // Rectangle placed{
    //     .x = best_rectangle.x-m_PADDING,
    //     .y = best_rectangle.y-m_PADDING,
    //     .width = width+(m_PADDING<<1),
    //     .height = height+(m_PADDING<<1),
    // };
    Rectangle placed{
        .x = best_rectangle.x,
        .y = best_rectangle.y,
        .width = width,
        .height = height,
    };

    // split rectangles
    std::vector<Rectangle> rectangles;

    for (const Rectangle &rectangle : m_rectangles) {
        if (intersect(rectangle, placed)) {
            split_rectangle(rectangle, placed, rectangles);
        } else {
            rectangles.emplace_back(rectangle);
        }
    }

    m_rectangles = std::move(rectangles);

    create_uv(image.path(), placed);

    return true;
}

bool Atlas::can_add_texture(int width, int height) {
    for (const Rectangle &rectangle : m_rectangles) {
        if (width <= rectangle.width && height <= rectangle.height) {
            return true;
        }
    }

    return false;
}

int Atlas::calculate_score(int width, int height, const Rectangle &rectangle) {
    return best_area_fit(width, height, rectangle);
}

int Atlas::best_area_fit(int width, int height, const Rectangle &rectangle) {
    return rectangle.width * rectangle.height - width * height;
}

void Atlas::place_image(const std::vector<std::uint8_t> &image_data, int x, int y, int width, int height) {
    for (int dy = 0; dy < height; ++dy) {
        for (int dx = 0; dx < width; ++dx) {
            int image_data_offset = +(dy * width + dx) * m_CHANNELS;

            std::uint8_t r = image_data[image_data_offset + 0];
            std::uint8_t g = image_data[image_data_offset + 1];
            std::uint8_t b = image_data[image_data_offset + 2];
            std::uint8_t a = image_data[image_data_offset + 3];

            int data_offset = ((y + dy) * m_MAX_WIDTH + (x + dx)) * m_CHANNELS;

            m_data[data_offset + 0] = r;
            m_data[data_offset + 1] = g;
            m_data[data_offset + 2] = b;
            m_data[data_offset + 3] = a;
        }
    }
}

bool Atlas::intersect(const Rectangle &a, const Rectangle &b) {
    int ax0 = a.x;
    int ax1 = a.x + a.width;
    int ay0 = a.y;
    int ay1 = a.y + a.height;

    int bx0 = b.x;
    int bx1 = b.x + b.width;
    int by0 = b.y;
    int by1 = b.y + b.height;

    return ax0 < bx1 && ax1 > bx0 && ay0 < by1 && ay1 > by0;
}

void Atlas::split_rectangle(const Rectangle &free, const Rectangle &placed, std::vector<Rectangle> &rectangles) {
    split_left(free, placed, rectangles);
    split_right(free, placed, rectangles);
    split_top(free, placed, rectangles);
    split_bottom(free, placed, rectangles);
}

void Atlas::split_left(const Rectangle &free, const Rectangle &placed, std::vector<Rectangle> &rectangles) {
    if (placed.x - m_PADDING <= free.x) {
        return;
    }

    Rectangle rectangle{
        .x = free.x,
        .y = free.y,
        .width = (placed.x - m_PADDING) - free.x,
        .height = free.height,
    };

    rectangles.emplace_back(std::move(rectangle));
}

void Atlas::split_right(const Rectangle &free, const Rectangle &placed, std::vector<Rectangle> &rectangles) {
    if (placed.x + placed.width + m_PADDING >= free.x + free.width) {
        return;
    }

    Rectangle rectangle{
        .x = placed.x + placed.width + m_PADDING,
        .y = free.y,
        .width = (free.x + free.width) - (placed.x + placed.width + m_PADDING),
        .height = free.height,
    };

    rectangles.emplace_back(std::move(rectangle));
}

void Atlas::split_top(const Rectangle &free, const Rectangle &placed, std::vector<Rectangle> &rectangles) {
    if (placed.y - m_PADDING <= free.y) {
        return;
    }

    Rectangle rectangle{
        .x = free.x,
        .y = free.y,
        .width = free.width,
        .height = (placed.y - m_PADDING) - free.y,
    };

    rectangles.emplace_back(std::move(rectangle));
}

void Atlas::split_bottom(const Rectangle &free, const Rectangle &placed, std::vector<Rectangle> &rectangles) {
    if (placed.y + placed.height + m_PADDING >= free.y + free.height) {
        return;
    }

    int x = free.x;
    int y = placed.y + placed.height + m_PADDING;
    int width = free.width;
    int height = (free.y + free.height) - (placed.y + placed.height + m_PADDING);

    rectangles.emplace_back(x, y, width, height);
}

void Atlas::create_uv(const std::string &path, const Rectangle &rectangle) {
    UV uv{
        .u0 = static_cast<float>(rectangle.x) / m_width,
        .u1 = static_cast<float>(rectangle.x + rectangle.width) / m_width,
        .v0 = static_cast<float>(rectangle.y) / m_height,
        .v1 = static_cast<float>(rectangle.y + rectangle.height) / m_height,
    };

    m_uvs.emplace(path, uv);
}

} // namespace engine::graphic::texture::atlas
