#pragma once

#include <glm/glm.hpp>

namespace game::parser::components {

struct HitObject {
    glm::ivec2 position; // actual position of the hit object
    int lane;            // lane of this hit object
    int start_time;
    int end_time;
    int hold_time;

    HitObject(glm::ivec2 &position, int lane, int start_time, int end_time, int hold_time) : position(position), lane(lane), start_time(start_time), end_time(end_time), hold_time(hold_time) {
    }
};

} // namespace game::parser::components
