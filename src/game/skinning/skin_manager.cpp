#include <vector>

#include <nlohmann/json_fwd.hpp>

#include "game/parser/beatmap.hpp"

#include "game/skinning/skin_manager.hpp"

#include "engine/graphic/texture/texture_manager.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

using namespace game::parser;
using namespace game::skinning::config;

using namespace engine::graphic::texture;

using namespace core::logger;
using namespace core::utility;

namespace game::skinning {

SkinManager::SkinManager() = default;

SkinManager::~SkinManager() = default;

SkinManager &SkinManager::get_instance() {
    static SkinManager instance;

    return instance;
}

void SkinManager::initialise() {
    for (const char *image_extension : m_IMAGE_EXTENSIONS) {
        m_image_extensions.emplace(image_extension);
    }
}

void SkinManager::load_textures(const std::string &path) {
    std::vector<std::string> texture_paths;

    std::deque<std::string> dq;
    dq.emplace_back(path);

    while (!dq.empty()) {
        int size = dq.size();

        for (int i = 0; i < size; ++i) {
            std::string &parent = dq.front();

            if (FileUtility::is_file(parent)) {
                std::string extension = FileUtility::get_extension_from_path(parent);

                if (m_image_extensions.contains(extension)) {
                    texture_paths.emplace_back(parent);
                }

                std::string filename = FileUtility::get_filename_from_path(parent);

                if (filename == m_CONFIGURATION_FILENAME) {
                    m_configuration_path = parent;
                }
            } else {
                std::vector<std::string> children = FileUtility::get_paths_in_directory(parent);

                for (std::string &child : children) {
                    dq.emplace_back(child);
                }
            }

            dq.pop_front();
        }
    }

    TextureManager &texture_manager = TextureManager::get_instance();

    for (auto &texture_path : texture_paths) {
        texture_manager.load_texture(texture_path);
    }
}

SkinConfig SkinManager::load_skin_config(Beatmap &beatmap) {
    int keys = beatmap.circle_size;

    SkinConfig skin_config(keys);

    nlohmann::json config;
    FileUtility::load_json(config, m_configuration_path);

    std::filesystem::path root(m_DEFAULT_PATH);

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
        Note &note = skin_config.notes[i];

        note.head = root / heads[i];
        note.body = root / bodies[i];
        note.tail = root / tails[i];

        note.width = widths[i];
    }

    std::vector<std::string> lighting_hold = data["lighting_hold"];

    for (const std::string &lighting : lighting_hold) {
        skin_config.lighting_hold.emplace_back(root / lighting);
    }

    std::vector<std::string> lighting_normal = data["lighting_normal"];

    for (const std::string &lighting : lighting_normal) {
        skin_config.lighting_normal.emplace_back(root / lighting);
    }

    skin_config.hit_position = data["hit_position"];
    skin_config.lighting_position = data["lighting_position"];

    skin_config.lighting_frame_rate = data["lighting_frame_rate"];

    skin_config.judge = root / data["judge"];

    return skin_config;
}

} // namespace game::skinning
