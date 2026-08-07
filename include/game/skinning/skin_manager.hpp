#pragma once

#include "engine/graphics/texture/texture_manager.hpp"
#include "game/importer/beatmap.hpp"
#include "game/skinning/config/skin_config.hpp"

#include <filesystem>
#include <string>
#include <unordered_set>

namespace game::skinning {

class SkinManager {
  public:
    explicit SkinManager(engine::graphics::texture::TextureManager &texture_manager);

    void load_textures(const std::filesystem::path &path);
    game::skinning::config::SkinConfig load_skin_config(const game::importer::Beatmap &beatmap);

  private:
    static inline const std::filesystem::path default_skin_path = "resources/skins/default";
    static inline const std::filesystem::path skin_configuration_file = "skin.config.json";

    static inline constexpr const char *image_extensions[] = {
        ".png",
        ".jpg",
    };

    std::unordered_set<std::string> m_image_extensions;
    std::filesystem::path m_root_path;
    std::filesystem::path m_configuration_path;

    engine::graphics::texture::TextureManager &m_texture_manager;
};

} // namespace game::skinning
