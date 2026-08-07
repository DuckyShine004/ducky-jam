#pragma once

#include <filesystem>

namespace game::skinning::config {

struct Note {
    std::filesystem::path head;
    std::filesystem::path body;
    std::filesystem::path tail;

    float width;
};

} // namespace game::skinning::config
