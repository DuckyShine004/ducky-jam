#pragma once

#include "parser/Parser.hpp"

#include "parser/beatmap/HitObject.hpp"
#include "parser/beatmap/TimingPoint.hpp"
#include "parser/beatmap/Difficulty.hpp"

namespace parser::beatmap {

class BeatmapParser final : public Parser {
  public:
    BeatmapParser();

    void parse(const std::string &path) override;

    std::vector<HitObject> getHitObjects();

    std::vector<TimingPoint> getTimingPoints();

    Difficulty getDifficulty();

  private:
    static constexpr int _HIT_OBJECT_IGNORE_FLAGS = 0b1010000;
    static constexpr int _TIMING_POINT_IGNORE_FLAGS = 0b10111000;
    static constexpr int _DIFFICULTY_IGNORE_FLAGS = 0b111000;

    Difficulty _difficulty;

    std::vector<HitObject> _hitObjects;

    std::vector<TimingPoint> _timingPoints;

    std::vector<std::string> getHitObjectValues(const std::string &line);

    std::vector<std::string> getTimingPointValues(const std::string &line);

    std::string getDifficultyValue(const std::string &line);

    void parseLine(const std::string &line, std::ifstream &file);

    void addHitObjects(std::ifstream &file);

    void addTimingPoints(std::ifstream &file);

    void addDifficulty(std::ifstream &file);
};

} // namespace parser::beatmap