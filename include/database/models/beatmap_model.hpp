#pragma once

#include <string>

namespace database::models {

struct BeatmapModel {
    int id = 0;
    int set_id = 0;

    std::string audio_title;
    std::string version;

    int key_count;
    float health_drain_rate;
    float overall_difficulty;

    int normal_notes = 0;
    int hold_notes = 0;

    std::string hash;
    std::string audio_hash;
    std::string background_hash;
};

} // namespace database::models
