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

        this->parseLine(line, file);
    }
}

std::vector<HitObject> BeatmapParser::getHitObjects() {
    return this->_hitObjects;
}

std::vector<TimingPoint> BeatmapParser::getTimingPoints() {
    return this->_timingPoints;
}

std::vector<std::string> BeatmapParser::getHitObjectValues(const std::string &line) {
    std::stringstream stream(line);

    std::string token;

    std::vector<std::string> hitObjectValues;

    int index = 0;

    hitObjectValues.reserve(5);

    while (std::getline(stream, token, ',')) {
        if (!(BitUtility::isBitSet(index, this->_HIT_OBJECT_IGNORE_FLAGS))) {
            hitObjectValues.push_back(token);
        }

        ++index;
    }

    return hitObjectValues;
}

std::vector<std::string> BeatmapParser::getTimingPointValues(const std::string &line) {
    std::stringstream stream(line);

    std::string token;

    std::vector<std::string> timingPointValues;

    int index = 0;

    timingPointValues.reserve(4);

    while (std::getline(stream, token, ',')) {
        if (!(BitUtility::isBitSet(index, this->_TIMING_POINT_IGNORE_FLAGS))) {
            timingPointValues.push_back(token);
        }

        ++index;
    }

    return timingPointValues;
}

void BeatmapParser::parseLine(const std::string &line, std::ifstream &file) {
    if (line == "[TimingPoints]") {
        this->addTimingPoints(file);
    } else if (line == "[HitObjects]") {
        this->addHitObjects(file);
    }
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

        std::vector<std::string> hitObjectValues = this->getHitObjectValues(line);

        int x = stoi(hitObjectValues[0]);
        int y = stoi(hitObjectValues[1]);
        int startTime = stoi(hitObjectValues[2]);
        int type = stoi(hitObjectValues[3]);
        int endTime = stoi(hitObjectValues[4]);

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

void BeatmapParser::addTimingPoints(std::ifstream &file) {
    std::string line;

    while (std::getline(file, line)) {
        line = StringUtility::trim(line);

        if (line.empty()) {
            break;
        }

        std::vector<std::string> timingPointValues = this->getTimingPointValues(line);

        int time = std::stoi(timingPointValues[0]);
        float beatLength = std::stof(timingPointValues[1]);
        int meter = std::stoi(timingPointValues[2]);
        bool isInherited = StringUtility::stob(timingPointValues[3]);

        TimingPoint timingPoint(time, beatLength, meter, isInherited);

        this->_timingPoints.push_back(timingPoint);
    }
}

} // namespace parser::beatmap