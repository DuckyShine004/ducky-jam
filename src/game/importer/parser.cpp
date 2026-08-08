#include "game/importer/parser.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/string_utility.hpp"
#include "game/importer/enums/hit_object_type.hpp"
#include "game/importer/enums/hit_sound_type.hpp"

#include <glm/fwd.hpp>

namespace game::importer {

namespace utility = core::utility;

Parser::Parser() {
}

void Parser::parse_line(const std::string &line, enums::Section &section) {
    switch (section) {
        case enums::Section::General:
            m_general.emplace_back(line);
            break;
        case enums::Section::Metadata:
            m_metadata.emplace_back(line);
            break;
        case enums::Section::Difficulty:
            m_difficulty.emplace_back(line);
            break;
        case enums::Section::Events:
            m_events.emplace_back(line);
            break;
        case enums::Section::TimingPoints:
            m_timing_points.emplace_back(line);
            break;
        case enums::Section::HitObjects:
            m_hit_objects.emplace_back(line);
            break;
        default:
            break;
    }
}

Beatmap Parser::parse() {
    Beatmap beatmap;

    parse_general(beatmap);
    parse_metadata(beatmap);
    parse_difficulty(beatmap);
    parse_events(beatmap);
    parse_timing_points(beatmap);
    parse_hit_objects(beatmap);

    return beatmap;
}

void Parser::parse_general(Beatmap &beatmap) {
    for (const std::string &line : m_general) {
        std::vector<std::string> split = utility::StringUtility::split_string(line, ':');

        const std::string &key = split[0];
        const std::string &value = utility::StringUtility::trim(split[1]);

        if (key == "AudioFilename") {
            beatmap.audio_filename = value;
        }
    }
}

void Parser::parse_metadata(Beatmap &beatmap) {
    for (const std::string &line : m_metadata) {
        std::vector<std::string> split = utility::StringUtility::split_string(line, ':');

        const std::string &key = split[0];
        const std::string &value = split.size() <= 1 ? "" : utility::StringUtility::trim(split[1]);

        if (key == "Title") {
            beatmap.title = value;
        } else if (key == "TitleUnicode") {
            beatmap.title_unicode = value;
        } else if (key == "Artist") {
            beatmap.artist = value;
        } else if (key == "ArtistUnicode") {
            beatmap.artist_unicode = value;
        } else if (key == "Creator") {
            beatmap.creator = value;
        } else if (key == "Version") {
            beatmap.version = value;
        } else if (key == "Source") {
            beatmap.source = value;
        } else if (key == "Tags") {
            beatmap.tags = value;
        }
    }
}

void Parser::parse_difficulty(Beatmap &beatmap) {
    for (const std::string &line : m_difficulty) {
        std::vector<std::string> split = utility::StringUtility::split_string(line, ':');

        const std::string &key = split[0];
        float value = std::stof(split[1]);

        if (key == "HPDrainRate") {
            beatmap.health_drain_rate = value;
        } else if (key == "CircleSize") {
            beatmap.circle_size = value;
        } else if (key == "OverallDifficulty") {
            beatmap.overall_difficulty = value;
        }
    }
}

void Parser::parse_events(Beatmap &beatmap) {
    for (const std::string &line : m_events) {
        std::vector<std::string> split = utility::StringUtility::split_string(line, ',');

        const std::string &event_type = split[0];

        if (event_type != "0") {
            continue;
        }

        int start_time = std::stoi(split[1]);

        beatmap.background_filename = utility::StringUtility::slice(split[2], 1, split[2].length() - 2);
    }
}

void Parser::parse_timing_points(Beatmap &beatmap) {
}

void Parser::parse_hit_objects(Beatmap &beatmap) {
    for (const std::string &line : m_hit_objects) {
        // split the string, split colons then parse
        std::vector<std::string> split = utility::StringUtility::split_string(line, ',');

        // WARN: unused for now, well most of it
        std::vector<std::string> colon = utility::StringUtility::split_string(split[5], ':');

        glm::ivec2 position(std::stoi(split[0]), std::stoi(split[1]));
        int start_time = std::stoi(split[2]);
        int type = std::stoi(split[3]);
        int hit_sound = std::stoi(split[4]);

        // WARN: Unused hit sound type
        enums::HitObjectType hit_object_type = static_cast<enums::HitObjectType>(type);
        enums::HitSoundType hit_sound_type = static_cast<enums::HitSoundType>(hit_sound);

        int lane = (int)std::floor(((float)position.x * beatmap.circle_size / 512.0f));
        int end_time = -1;

        if (hit_object_type == enums::HitObjectType::Hold) {
            end_time = std::stoi(colon[0]);
        }

        int hold_time = std::max(0, end_time - start_time);
        // LOG_INFO("Line: {} | Lane: {} | Hold: {}", line, lane, hold_time);

        // create hit object here
        beatmap.hit_objects.emplace_back(position, lane, start_time, end_time, hold_time);
    }
}

} // namespace game::importer
