#pragma once

#include "database/repositories/beatmap_repository.hpp"

#include <filesystem>
#include <string>
#include <unordered_set>
#include <vector>

namespace game::importer {

// Accepts .osz ONLY, skins should rely only on ducky jam schema
class Importer {
  public:
    Importer(database::repositories::BeatmapRepository &beatmap_repository);

    void import(const std::vector<std::filesystem::path> &paths);

  private:
    static inline constexpr const char *image_extensions[] = {
        ".png",
        ".jpg",
    };

    static inline constexpr const char *valid_extensions[] = {
        ".png",
        ".jpg",
        ".mp3",
        ".osu",
    };

    std::unordered_set<std::string> m_image_extensions;
    std::unordered_set<std::string> m_valid_extensions;

    /**
     * @brief Should return an array of paths to extracted files. Developers should check if the files are properly
     * extracted to the designated locations; IO errors are common.
     *
     * @param path the input path.
     */
    std::vector<std::filesystem::path> extract(const std::filesystem::path &path);

    database::repositories::BeatmapRepository &m_beatmap_repository;
};

} // namespace game::importer
