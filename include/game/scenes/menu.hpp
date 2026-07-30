#pragma once

#include "engine/scene/scene.hpp"

#include "game/ui/theme/theme_config.hpp"

namespace game::scenes {

class Menu final : public engine::scene::Scene {
  public:
    Menu(const game::ui::theme::ThemeConfig &theme_config);

    void update(double delta_time) override;
    void update_by_audio(engine::audio::AudioBuffer &audio_buffer, double track_time) override;

  private:
    static std::unique_ptr<engine::ui::UiNode> create_root(const game::ui::theme::ThemeConfig &theme_config);
};

} // namespace game::scenes
