#pragma once

#include "engine/graphics/drawable/drawable.hpp"

namespace game::gameplay::stage {

struct Note {
    double x;
    double y;

    double width;
    double height;

    double start_time;
    double end_time;
};

} // namespace game::gameplay::stage
