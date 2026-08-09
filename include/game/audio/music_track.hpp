#pragma once

#include <filesystem>
#include <string>

namespace game::audio {

struct MusicTrack {
    std::string filename;
    std::filesystem::path path;
};

} // namespace game::audio
