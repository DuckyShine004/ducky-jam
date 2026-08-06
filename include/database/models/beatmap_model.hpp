#pragma once

#include <string>

namespace database::models {

struct BeatmapModel {
    int id;
    int set_id;

    std::string version;

    int key_count;
    float health_drain_rate;
    float overall_difficulty;

    int normal_notes;
    int hold_notes;

    std::string audio_hash;
    std::string background_hash;
};

} // namespace database::models
