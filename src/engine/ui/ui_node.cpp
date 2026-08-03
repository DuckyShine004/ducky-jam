#include <algorithm>
#include <cmath>

#include "engine/ui/ui_node.hpp"

#include "engine/graphics/model/quad.hpp"
#include "engine/graphics/effect/quad_effect.hpp"
#include "engine/graphics/texture/texture_manager.hpp"
#include "engine/graphics/shader/shader_manager.hpp"

using namespace core::structs;

using namespace engine::ui::enums;
using namespace engine::ui::components;

using namespace engine::audio;

using namespace engine::graphics::model;
using namespace engine::graphics::shader;
using namespace engine::graphics::renderer;
using namespace engine::graphics::effect;
using namespace engine::graphics::texture;

namespace engine::ui {

void UiNode::add_child(std::unique_ptr<UiNode> child) {
    m_children.emplace_back(std::move(child));
}

Vector2<float> UiNode::measure(Constraint &constraint) {
    const float horizontal_padding = m_layout.padding.left + m_layout.padding.right;
    const float vertical_padding = m_layout.padding.top + m_layout.padding.bottom;

    Constraint content_constraint{
        .minimum = {0.0f, 0.0f},
        .maximum =
            {
                std::max(0.0f, constraint.maximum.w - horizontal_padding),
                std::max(0.0f, constraint.maximum.h - vertical_padding),
            },
    };

    Vector2<float> content_size{0.0f, 0.0f};

    // WARN: This aggregation specifically describes a vertical container
    for (auto &child : m_children) {
        const Margin &margin = child->layout().margin;

        Constraint child_constraint{
            .minimum = {0.0f, 0.0f},
            .maximum =
                {
                    std::max(0.0f, content_constraint.maximum.w - margin.left - margin.right),
                    std::max(0.0f, content_constraint.maximum.h - margin.top - margin.bottom),
                },
        };

        Vector2<float> child_size = child->measure(child_constraint);

        content_size.w = std::max(content_size.w, child_size.w + margin.left + margin.right);
        content_size.h += child_size.h + margin.top + margin.bottom;
    }

    Vector2<float> desired_size{
        content_size.w + horizontal_padding,
        content_size.h + vertical_padding,
    };

    const bool automatic_width = m_layout.width == Layout::MAX_WIDTH;
    const bool automatic_height = m_layout.height == Layout::MAX_HEIGHT;

    if (!automatic_width) {
        desired_size.w = m_layout.width;
    }

    if (!automatic_height) {
        desired_size.h = m_layout.height;
    }

    desired_size.w = std::clamp(desired_size.w, constraint.minimum.w, constraint.maximum.w);
    desired_size.h = std::clamp(desired_size.h, constraint.minimum.h, constraint.maximum.h);

    m_size = desired_size;

    return m_size;
}

void UiNode::arrange(const Bound &bound) {
    m_bound = bound;

    Bound content{
        .x = bound.x + m_layout.padding.left,
        .y = bound.y + m_layout.padding.top,
        .width = std::max(0.0f, bound.width - m_layout.padding.left - m_layout.padding.right),
        .height = std::max(0.0f, bound.height - m_layout.padding.top - m_layout.padding.bottom),
    };

    for (auto &child : m_children) {
        const Margin &margin = child->layout().margin;

        Vector2<float> child_size = child->m_size;

        Bound available{
            .x = content.x + margin.left,
            .y = content.y + margin.top,
            .width = std::max(0.0f, content.width - margin.left - margin.right),
            .height = std::max(0.0f, content.height - margin.top - margin.bottom),
        };

        Vector2<float> position = get_aligned_position(available, child_size, child->layout().align);

        child->arrange({
            .x = position.x,
            .y = position.y,
            .width = child_size.w,
            .height = child_size.h,
        });
    }
}

void UiNode::update(double delta_time) {
    for (std::unique_ptr<UiNode> &child : m_children) {
        child->update(delta_time);
    }
}

void UiNode::update_by_audio(AudioBuffer &audio_buffer, double track_time) {
    for (std::unique_ptr<UiNode> &child : m_children) {
        child->update_by_audio(audio_buffer, track_time);
    }
}

void UiNode::submit(Renderer &renderer) const {
    const bool has_shadow = m_layout.shadow.colour.a > 0;
    const float blur = has_shadow ? std::max(0.0f, m_layout.shadow.blur_radius) : 0.0f;
    const float shadow_extent = has_shadow ? std::max(std::abs(m_layout.shadow.offset_x), std::abs(m_layout.shadow.offset_y)) : 0.0f;
    const float padding = blur * 3.0f + shadow_extent;

    const Vector2<float> draw_size{
        m_bound.width + padding * 2.0f,
        m_bound.height + padding * 2.0f,
    };

    const EffectPtr quad_effect = std::make_shared<QuadEffect>(
        ShaderManager::get_instance().get_shader_id("quad"), draw_size, Vector2<float>{m_bound.width, m_bound.height}, m_layout.border.radius, Vector2<float>{m_layout.shadow.offset_x, -m_layout.shadow.offset_y}, blur, m_layout.shadow.colour, std::max(0.0f, m_layout.bloom.intensity));

    const float draw_x = m_bound.x - padding;
    const float draw_top = m_bound.y - padding;
    const float draw_y = 1440.0f - draw_top - draw_size.h;

    TextureManager &texture_manager = TextureManager::get_instance();

    renderer.queue(Quad{
        .x = draw_x,
        .y = draw_y,
        .width = draw_size.w,
        .height = draw_size.h,
        .texture_id = texture_manager.get_texture_id("resources/core/textures/colours/white.png"),
        .effect = quad_effect,
        .colour = m_layout.colour,
    });

    for (const std::unique_ptr<UiNode> &child : m_children)
        child->submit(renderer);
}

Layout &UiNode::layout() {
    return m_layout;
}

Vector2<float> UiNode::get_aligned_position(const Bound &available, const Vector2<float> &child_size, Align align) {
    float left = available.x;
    float centre_x = available.x + (available.width - child_size.w) * 0.5f;
    float right = available.x + available.width - child_size.w;
    float top = available.y;
    float centre_y = available.y + (available.height - child_size.h) * 0.5f;
    float bottom = available.y + available.height - child_size.h;

    switch (align) {
        case Align::TopLeft:
            return {left, top};

        case Align::Top:
            return {centre_x, top};

        case Align::TopRight:
            return {right, top};

        case Align::Left:
        case Align::LeftCentre:
            return {left, centre_y};

        case Align::Centre:
            return {centre_x, centre_y};

        case Align::Right:
        case Align::RightCentre:
            return {right, centre_y};

        case Align::BottomLeft:
            return {left, bottom};

        case Align::Bottom:
            return {centre_x, bottom};

        case Align::BottomRight:
            return {right, bottom};
    }

    return {left, top};
}

} // namespace engine::ui
