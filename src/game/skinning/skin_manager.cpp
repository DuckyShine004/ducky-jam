#include "game/skinning/skin_manager.hpp"

#include "core/utility/file_utility.hpp"
#include "core/utility/json_utility.hpp"
#include "engine/graphics/texture/texture_manager.hpp"
#include "game/importer/beatmap.hpp"

#include <nlohmann/json_fwd.hpp>

#include <deque>
#include <filesystem>
#include <vector>

namespace game::skinning {

namespace utility = core::utility;
namespace graphics = engine::graphics;

SkinManager::SkinManager(graphics::texture::TextureManager &texture_manager) : m_root_path(default_skin_path), m_configuration_path(default_skin_path / skin_configuration_file), m_texture_manager(texture_manager) {
    for (const char *image_extension : image_extensions) {
        m_image_extensions.emplace(image_extension);
    }
}

void SkinManager::load_textures(const std::filesystem::path &path) {
    m_root_path = path;
    m_configuration_path = path / skin_configuration_file;

    std::vector<std::filesystem::path> texture_paths;
    std::deque<std::filesystem::path> dq;

    dq.emplace_back(path);

    while (!dq.empty()) {
        int size = dq.size();

        for (int i = 0; i < size; ++i) {
            std::filesystem::path parent = dq.front();
            dq.pop_front();

            if (utility::FileUtility::is_file(parent)) {
                std::string extension = utility::FileUtility::extension(parent);

                if (m_image_extensions.contains(extension)) {
                    texture_paths.emplace_back(parent);
                }

                if (parent.filename() == skin_configuration_file) {
                    m_configuration_path = parent;
                }
            } else {
                const std::vector<std::filesystem::path> children = utility::FileUtility::children(parent);

                for (const std::filesystem::path &child : children) {
                    dq.emplace_back(child);
                }
            }
        }
    }

    for (const std::filesystem::path &texture_path : texture_paths) {
        m_texture_manager.load_texture(texture_path);
    }
}

config::SkinConfig SkinManager::load_skin_config(const importer::Beatmap &beatmap) {
    int keys = beatmap.circle_size;

    config::SkinConfig skin_config(keys);

    nlohmann::json config;
    utility::JsonUtility::load(config, m_configuration_path);

    nlohmann::json data;

    for (auto &property : config) {
        if (property["keys"] == keys) {
            data = property;
            break;
        }
    }

    std::vector<std::string> heads = data["heads"];
    std::vector<std::string> tails = data["tails"];
    std::vector<std::string> bodies = data["bodies"];

    std::vector<float> widths = data["widths"];

    skin_config.height = data["height"];

    for (int i = 0; i < heads.size(); ++i) {
        config::Note &note = skin_config.notes[i];

        note.head = m_root_path / heads[i];
        note.body = m_root_path / bodies[i];
        note.tail = m_root_path / tails[i];

        note.width = widths[i];
    }

    std::vector<std::string> lighting_hold = data["lighting_hold"];

    for (const std::string &lighting : lighting_hold) {
        skin_config.lighting_hold.emplace_back(m_root_path / lighting);
    }

    std::vector<std::string> lighting_normal = data["lighting_normal"];

    for (const std::string &lighting : lighting_normal) {
        skin_config.lighting_normal.emplace_back(m_root_path / lighting);
    }

    skin_config.hit_position = data["hit_position"];
    skin_config.lighting_position = data["lighting_position"];

    skin_config.lighting_frame_rate = data["lighting_frame_rate"];

    skin_config.judge = m_root_path / data["judge"].get<std::string>();

    return skin_config;
}

} // namespace game::skinning
