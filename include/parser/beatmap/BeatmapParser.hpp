#pragma once

#include <parser/Parser.hpp>

#include <parser/beatmap/HitObject.hpp>
#include <parser/beatmap/TimingPoint.hpp>

namespace parser::beatmap {

class BeatmapParser final : public Parser {
  public:
    BeatmapParser();

    void parse(const std::string &path) override;

    std::vector<HitObject> getHitObjects();

    std::vector<TimingPoint> getTimingPoints();

  private:
    static constexpr int _HIT_OBJECT_IGNORE_FLAGS = 0b1010000;
    static constexpr int _TIMING_POINT_IGNORE_FLAGS = 0b10111000;

    std::vector<HitObject> _hitObjects;

    std::vector<TimingPoint> _timingPoints;

    std::vector<std::string> getHitObjectValues(const std::string &line);

    std::vector<std::string> getTimingPointValues(const std::string &line);

    void parseLine(const std::string &line, std::ifstream &file);

    void addHitObjects(std::ifstream &file);

    void addTimingPoints(std::ifstream &file);
};

} // namespace parser::beatmap