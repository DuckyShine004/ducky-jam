// x, y, time, type, hitSound, endTime, hitSample

#include <parser/beatmap/BeatmapParser.hpp>

#include <utility/string/StringUtility.hpp>

#include <logger/LoggerMacros.hpp>

#include <fstream>

using namespace utility::string;

namespace parser::beatmap {

BeatmapParser::BeatmapParser() : Parser() {
}

void BeatmapParser::parse(const std::string &path) {
    std::ifstream file(path);

    std::string line;

    while (std::getline(file, line)) {
        line = StringUtility::trim(line);

        if (line == "[General]") {
            addHitObjects(file);
        }
    }
}

std::vector<HitObject> BeatmapParser::getHitObjects() {
    return this->_hitObjects;
}

void BeatmapParser::addHitObjects(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        line = StringUtility::trim(line);

        if (line.empty()) {
            LOG_DEBUG("BRUH");
        }

        std::stringstream ss(line);

        std::string token;

        // 1) x
        std::getline(ss, token, ',');
        int x = std::stoi(token);

        // 2) y
        std::getline(ss, token, ',');
        int y = std::stoi(token);

        // 3) time
        std::getline(ss, token, ',');
        int timeMs = std::stoi(token);

        // 4) type
        std::getline(ss, token, ',');
        int type = std::stoi(token);

        // 5) hitSound (we skip it)
        std::getline(ss, token, ',');

        // 6) endTime
        std::getline(ss, token, ',');
        int endTime = std::stoi(token);
    }
}

} // namespace parser::beatmap