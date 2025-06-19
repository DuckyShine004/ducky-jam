// x, y, time, type, hitSound, endTime, hitSample

#include <parser/beatmap/BeatmapParser.hpp>

#include <utility/string/StringUtility.hpp>

#include <utility/bit/BitUtility.hpp>

#include <logger/LoggerMacros.hpp>

#include <limits>
#include <fstream>

using namespace utility::string;

using namespace utility::bit;

namespace parser::beatmap {

BeatmapParser::BeatmapParser() : Parser() {
}

void BeatmapParser::parse(const std::string &path) {
    std::ifstream file(path);

    std::string line;

    while (std::getline(file, line)) {
        line = StringUtility::trim(line);

        if (line == "[HitObjects]") {
            addHitObjects(file);
        }
    }
}

std::vector<HitObject> BeatmapParser::getHitObjects() {
    return this->_hitObjects;
}

std::vector<int> BeatmapParser::getHitObjectValues(const std::string &line) {
    std::stringstream stream(line);

    std::string token;

    std::vector<int> hitObjectValues;

    int index = 0;

    hitObjectValues.reserve(5);

    while (std::getline(stream, token, ',')) {
        if (!(BitUtility::isBitSet(index, this->_HIT_OBJECT_IGNORE_FLAGS))) {
            int value = std::stoi(token);

            hitObjectValues.push_back(value);
        }

        ++index;
    }

    return hitObjectValues;
}

void BeatmapParser::addHitObjects(std::ifstream &file) {
    std::string line;

    int first = std::numeric_limits<int>::max();
    int second = std::numeric_limits<int>::max();

    while (std::getline(file, line)) {
        line = StringUtility::trim(line);

        if (line.empty()) {
            break;
        }

        std::vector<int> hitObjectValues = this->getHitObjectValues(line);

        int x = hitObjectValues[0];
        int y = hitObjectValues[1];
        int startTime = hitObjectValues[2];
        int type = hitObjectValues[3];
        int endTime = hitObjectValues[4];

        if (x < first) {
            second = first;
            first = x;
        } else if (x > first && x < second) {
            second = x;
        }

        HitObject hitObject(x, y, type, startTime, endTime);

        this->_hitObjects.push_back(hitObject);
    }

    if (second == std::numeric_limits<int>::max()) {
        second = first;
    }

    int offset = first;
    int size = second - first;

    for (HitObject &hitObject : this->_hitObjects) {
        hitObject.calculateLane(offset, size);
    }
}

} // namespace parser::beatmap