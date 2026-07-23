#pragma once

#include <vector>
#include <string>

#include "game/skinning/config/note.hpp"

namespace game::skinning::config {

struct SkinConfig {
    std::vector<game::skinning::config::Note> notes;

    std::vector<std::string> lighting;

    SkinConfig(int keys = 0) {
        for (int i = 0; i < keys; ++i) {
            notes.emplace_back();
        }
    }
};

} // namespace game::skinning::config
