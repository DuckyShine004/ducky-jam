#pragma once

#include "engine/scene/scene.hpp"

namespace game::scenes {

class Menu final : public engine::scene::Scene {
  public:
    Menu();

  private:
    static std::unique_ptr<engine::ui::UiNode> create_root();
};

} // namespace game::scenes
