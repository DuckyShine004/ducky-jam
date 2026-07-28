#pragma once

#include <vector>
#include <memory>

#include "engine/graphic/drawable/drawable_node.hpp"

#include "engine/ui/components/layout.hpp"

namespace engine::ui {

class UiNode : public engine::graphic::drawable::DrawableNode {
  public:
    virtual ~UiNode() = default;

    UiNode(const UiNode &) = delete;
    UiNode &operator=(const UiNode &) = delete;

    UiNode(UiNode &&) noexcept = default;
    UiNode &operator=(UiNode &&) noexcept = default;

    template <typename... Children>
    requires(std::derived_from<std::remove_cvref_t<Children>, UiNode> && ...)
    UiNode(const components::Layout &layout, Children &&...children) : m_layout(std::move(layout)) {
        // m_children.emplace_back((std::move(std::make_unique<std::remove_cvref_t<Children>>(std::forward<Children>(children))), ...));
        // (add_child(std::move(std::make_unique<std::remove_cvref_t<Children>>(std::forward<Children>(children)))), ...);
        (add_child(std::make_unique<std::remove_cvref_t<Children>>(std::forward<Children>(children))), ...);
    }

    void add_child(std::unique_ptr<UiNode> child);

    components::Layout &layout() const;

  protected:
    components::Layout m_layout;

    std::vector<std::unique_ptr<UiNode>> m_children;
};

} // namespace engine::ui
