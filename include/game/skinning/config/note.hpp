#pragma once

#include <string>

namespace game::skinning::config {

struct Note {
    std::string head;
    std::string body;
    std::string tail;

    float width;
    float height;
};

} // namespace game::skinning::config
