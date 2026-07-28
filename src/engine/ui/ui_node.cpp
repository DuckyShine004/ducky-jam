#include "engine/ui/ui_node.hpp"

using namespace engine::ui::components;

namespace engine::ui {

void UiNode::add_child(std::unique_ptr<UiNode> child) {
    m_children.emplace_back(std::move(child));
}

} // namespace engine::ui
