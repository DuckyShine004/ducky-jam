#pragma once

#include "engine/ui/ui_node.hpp"

#include "engine/graphic/render/renderer.hpp"

namespace engine::scene {

class Scene {
  public:
    virtual ~Scene() = default;

    void submit(graphic::render::Renderer &renderer);

  protected:
    explicit Scene(std::unique_ptr<engine::ui::UiNode> root) : m_root(std::move(root)) {
    }

    std::unique_ptr<engine::ui::UiNode> m_root;
};

} // namespace engine::scene
