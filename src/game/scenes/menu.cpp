#include "engine/ui/enums/align.hpp"
#include "engine/ui/components/layout.hpp"
#include "engine/ui/spectrum.hpp"
#include "engine/ui/container.hpp"

#include "game/scenes/menu.hpp"

using namespace engine::audio;

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
        },
        Spectrum{
            Layout{
                .width = 2560,
                .height = 360,
                .align = Align::Bottom,
                .colour = theme_config.theme.spectrum,
            },
            128,
            10.0f,
        });
}

void Menu::update(double delta_time) {
    m_root->update(delta_time);
}

void Menu::update_by_audio(AudioBuffer &audio_buffer, double track_time) {
    m_root->update_by_audio(audio_buffer, track_time);
}

} // namespace game::scenes
