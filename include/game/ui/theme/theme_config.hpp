#pragma once

#include <string>
#include <nlohmann/json_fwd.hpp>

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/colour_utility.hpp"

#include "game/ui/theme/theme.hpp"

/* NOTE: SHould change, bad pattern, always bad to rely on static method */
namespace game::ui::theme {

struct ThemeConfig {
    static inline constexpr const char *CONFIGURATION_PATH = "resources/core/ui/themes/default.json";

    Theme theme;

    static ThemeConfig load(const std::string &path = CONFIGURATION_PATH) {
        LOG_INFO("Loading theme: {}", CONFIGURATION_PATH);

        nlohmann::json theme_config;
        core::utility::FileUtility::load_json(theme_config, CONFIGURATION_PATH);

        std::unordered_map<std::string, std::string> colours;

        for (const auto &[key, value] : theme_config["colours"].items()) {
            colours[key] = value;
        }

        const auto &scheme = theme_config["scheme"];

        ThemeConfig config;

        config.theme.background = core::utility::ColourUtility::hex_to_rgba(colours[scheme["background"]]);
        config.theme.topbar = core::utility::ColourUtility::hex_to_rgba(colours[scheme["topbar"]]);
        config.theme.spectrum = core::utility::ColourUtility::hex_to_rgba(colours[scheme["spectrum"]]);

        return config;
    }
};

} // namespace game::ui::theme
