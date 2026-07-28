#pragma once

#include "engine/ui/ui_node.hpp"

namespace engine::scene {

class Scene {
  public:
    virtual ~Scene() = default;

  protected:
    explicit Scene(std::unique_ptr<engine::ui::UiNode> root) : m_root(std::move(root)) {
    }

    std::unique_ptr<engine::ui::UiNode> m_root;
};

} // namespace engine::scene
