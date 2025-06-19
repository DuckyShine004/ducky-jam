// x, y, time, type, hitSound, endTime, hitSample

#include <parser/beatmap/BeatmapParser.hpp>

#include <logger/LoggerMacros.hpp>

#include <fstream>

namespace parser::beatmap {

BeatmapParser::BeatmapParser() : Parser() {
}

void BeatmapParser::parse(const std::string &path) {
    std::ifstream file(path);

    std::string line;

    while (std::getline(file, line)) {
        // if (line[0] != '[') {
        //     continue;
        // }

        if (line == "[General]") {
            addHitObjects(file);
        }
    }
}

void BeatmapParser::addHitObjects(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        LOG_DEBUG(line);
        if (line.empty()) {
            LOG_DEBUG("BRUH");
        }
    }
}

} // namespace parser::beatmap