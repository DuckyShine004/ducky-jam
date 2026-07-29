#include "engine/ui/container.hpp"
#include "engine/ui/enums/align.hpp"
#include "engine/ui/components/layout.hpp"

#include "game/scenes/menu.hpp"

using namespace engine::ui;
using namespace engine::ui::enums;
using namespace engine::ui::components;

using namespace game::ui::theme;

namespace game::scenes {

Menu::Menu(const ThemeConfig &theme_config) : Scene(create_root(theme_config)) {
}

std::unique_ptr<UiNode> Menu::create_root(const ThemeConfig &theme_config) {
    return std::make_unique<Container>(
        Layout{
            .width = 2560,
            .height = 1440,
            .align = Align::TopLeft,
            .colour = theme_config.theme.background,
        },
        Container{
            Layout{
                .width = 2560,
                .height = 80,
                .align = Align::TopLeft,
                .shadow =
                    {
                        .blur_radius = 10.0f,
                        .colour = {0, 0, 0, 100},
                    },
                .colour = theme_config.theme.topbar,
            },
        });
}

} // namespace game::scenes
