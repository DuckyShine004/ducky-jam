#pragma once

#include <string>

#include "game/parser/components/hit_object.hpp"

namespace game::parser {

class Beatmap {
  public:
    std::string audio_filename;

    std::string title;
    std::string title_unicode;
    std::string artist;
    std::string artist_unicode;
    std::string creator;
    std::string version;
    std::string source;
    std::string tags;

    std::string background_filename;

    float health_drain_rate;
    float circle_size;
    float overall_difficulty;

    std::vector<game::parser::components::HitObject> hit_objects;
};

} // namespace game::parser
