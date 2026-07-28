#include "engine/ui/components/layout.hpp"

#include "engine/ui/enums/align.hpp"

#include "engine/ui/container.hpp"

#include "game/scenes/menu.hpp"

using namespace engine::ui;
using namespace engine::ui::enums;
using namespace engine::ui::components;

namespace game::scenes {

Menu::Menu() : Scene(create_root()) {
}

std::unique_ptr<UiNode> Menu::create_root() {
    return std::make_unique<Container>(
        Layout{
            .width = 2560,
            .height = 1440,
            .align = Align::TopLeft,
            .colour = {0, 0, 0, 0},
        },
        Container{Layout{
            .width = 2560,
            .height = 40,
            .align = Align::TopLeft,
            .colour = {255, 255, 255, 255},
        }});
}

} // namespace game::scenes
