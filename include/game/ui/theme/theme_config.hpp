#pragma once

#include "core/logger/logger_macros.hpp"
#include "core/utility/colour_utility.hpp"
#include "core/utility/json_utility.hpp"
#include "game/ui/theme/theme.hpp"

#include <nlohmann/json_fwd.hpp>

#include <filesystem>

/* NOTE: SHould change, bad pattern, always bad to rely on static method */
namespace game::ui::theme {

struct ThemeConfig {
    static inline const std::filesystem::path default_configuration_path = "resources/core/ui/themes/default.json";

    Theme theme;

    static ThemeConfig load(const std::filesystem::path &path = default_configuration_path) {
        LOG_INFO("Loading theme: {}", path.string());

        nlohmann::json theme_config;
        core::utility::JsonUtility::load(theme_config, path);

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
