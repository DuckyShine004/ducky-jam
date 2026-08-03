#pragma once

#include <vector>
#include <memory>

#include "core/structs/vector2.hpp"

#include "engine/graphics/renderer/renderer.hpp"

#include "engine/audio/audio_buffer.hpp"

#include "engine/ui/bound.hpp"
#include "engine/ui/constraint.hpp"
#include "engine/ui/components/layout.hpp"

namespace engine::ui {

class UiNode : public engine::graphics::drawable::Drawable {
  public:
    virtual ~UiNode() = default;

    UiNode(const UiNode &) = delete;
    UiNode &operator=(const UiNode &) = delete;

    UiNode(UiNode &&) noexcept = default;
    UiNode &operator=(UiNode &&) noexcept = default;

    template <typename... Children>
    requires(std::derived_from<std::remove_cvref_t<Children>, UiNode> && ...)
    UiNode(const components::Layout &layout, Children &&...children) : m_layout(std::move(layout)) {
        (add_child(std::make_unique<std::remove_cvref_t<Children>>(std::forward<Children>(children))), ...);
    }

    void add_child(std::unique_ptr<UiNode> child);

    core::structs::Vector2<float> measure(Constraint &constraint);
    virtual void arrange(const Bound &bound);

    virtual void update(double delta_time);
    virtual void update_by_audio(engine::audio::AudioBuffer &audio_buffer, double track_time);

    void submit(engine::graphics::renderer::Renderer &renderer) const override;

    components::Layout &layout();

  protected:
    virtual core::structs::Vector2<float> get_aligned_position(const Bound &bound, const core::structs::Vector2<float> &child_size, enums::Align align);

    core::structs::Vector2<float> m_size;

    Bound m_bound;

    components::Layout m_layout;

    std::vector<std::unique_ptr<UiNode>> m_children;
};

} // namespace engine::ui
