#include "game/scenes/menu.hpp"

#include "engine/ui/components/layout.hpp"
#include "engine/ui/container.hpp"
#include "engine/ui/enums/align.hpp"
#include "game/ui/spectrum.hpp"

namespace game::scenes {

namespace audio = engine::audio;

namespace game_ui = game::ui;
namespace engine_ui = engine::ui;

Menu::Menu(const game_ui::theme::ThemeConfig &theme_config) : Scene(create_root(theme_config)) {
}

std::unique_ptr<engine_ui::UiNode> Menu::create_root(const game_ui::theme::ThemeConfig &theme_config) {
    return std::make_unique<engine_ui::Container>(
        engine_ui::components::Layout{
            .width = 2560,
            .height = 1440,
            .align = engine_ui::enums::Align::TopLeft,
            .colour = theme_config.theme.background,
        },
        engine_ui::Container{
            engine_ui::components::Layout{
                .width = 2560,
                .height = 80,
                .align = engine_ui::enums::Align::TopLeft,
                .shadow =
                    {
                        .blur_radius = 10.0f,
                        .colour = {0, 0, 0, 100},
                    },
                .colour = theme_config.theme.topbar,
            },
        },
        game_ui::Spectrum{
            engine_ui::components::Layout{
                .width = 2560,
                .height = 480,
                .align = engine_ui::enums::Align::Bottom,
                .bloom =
                    {
                        .intensity = 0.1f,
                    },
                .colour = theme_config.theme.spectrum,
            },
            64,
            10.0f,
        });
}

void Menu::update(double delta_time) {
    m_root->update(delta_time);
}

void Menu::update_by_audio(audio::AudioBuffer &audio_buffer, double track_time) {
    m_root->update_by_audio(audio_buffer, track_time);
}

} // namespace game::scenes
