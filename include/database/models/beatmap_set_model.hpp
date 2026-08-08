#pragma once

#include <string>

namespace database::models {

struct BeatmapSetModel {
    int id = 0;

    std::string title;
    std::string title_unicode;
    std::string artist;
    std::string artist_unicode;
    std::string creator;
    std::string source;
    std::string tags;

    int date_added;
};

} // namespace database::models
