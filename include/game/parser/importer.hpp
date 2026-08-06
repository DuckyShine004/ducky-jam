#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace game::parser {

// Accepts .osz ONLY, skins should rely only on ducky jam schema
class Importer {
  public:
    Importer() = default;

    void import(const std::vector<std::string> &paths);

  private:
    // NOTE: Should use cache directory to store audio, that way if game is deleted, we can still rely on cache, test with core/ in development
    static inline constexpr const char *m_OUTPUT_DIRECTORY = "resources/tmp";

    std::vector<std::string> extract(const std::string &path);

    std::unordered_map<std::string, std::string> handle_audio_files(const std::vector<std::string> &paths);
    void handle_beatmap_files(const std::vector<std::string> &paths, const std::unordered_map<std::string, std::string> &audio_hashes);
};

} // namespace game::parser
