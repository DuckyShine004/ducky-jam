#pragma once

#include "game/parser/components/hit_object.hpp"

namespace game::parser {

class Beatmap {
  public:
    float health_drain_rate;
    float circle_size;
    float overall_difficulty;

    std::vector<game::parser::components::HitObject> hit_objects;
};

} // namespace game::parser
