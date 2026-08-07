#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>
#include <vector>

namespace game::importer {

// Accepts .osz ONLY, skins should rely only on ducky jam schema
class Importer {
  public:
    Importer();

    void import(const std::vector<std::filesystem::path> &paths);

  private:
    /**
     * @brief Should return an array of paths to extracted files.
     *
     * @param path
     */
    std::vector<std::filesystem::path> extract(const std::filesystem::path &path);

    std::unordered_map<std::string, std::string> handle_audio_files(const std::vector<std::filesystem::path> &paths);
    void handle_beatmap_files(const std::vector<std::filesystem::path> &paths, const std::unordered_map<std::string, std::string> &audio_hashes);
};

} // namespace game::importer
