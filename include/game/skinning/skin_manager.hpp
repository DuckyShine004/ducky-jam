#pragma once

#include <string>
#include <unordered_set>

#include "game/parser/beatmap.hpp"

#include "game/skinning/config/skin_config.hpp"

namespace game::skinning {

class SkinManager {
  public:
    SkinManager(const SkinManager &) = delete;
    SkinManager &operator=(const SkinManager &) = delete;

    static SkinManager &get_instance();

    void initialise();
    void load_textures(const std::string &path = m_DEFAULT_PATH);
    game::skinning::config::SkinConfig load_skin_config(game::parser::Beatmap &beatmap);

  private:
    SkinManager();
    ~SkinManager();

    static inline constexpr const char *m_DEFAULT_PATH = "resources/skins/default";
    static inline constexpr const char *m_CONFIGURATION_FILENAME = "skin.config.json";

    static inline constexpr const char *m_IMAGE_EXTENSIONS[] = {
        ".png",
        ".jpg",
    };

    std::unordered_set<std::string> m_image_extensions;
    std::string m_configuration_path;
};

} // namespace game::skinning
