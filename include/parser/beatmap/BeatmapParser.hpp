#pragma once

#include <parser/Parser.hpp>

#include <parser/beatmap/HitObject.hpp>

namespace parser::beatmap {

class BeatmapParser final : public Parser {
  public:
    BeatmapParser();

    void parse(const std::string &path) override;

    std::vector<HitObject> getHitObjects();

  private:
    static constexpr int _HIT_OBJECT_IGNORE_FLAGS = 0b1010000;

    std::vector<HitObject> _hitObjects;

    std::vector<int> getHitObjectValues(const std::string &line);

    void addHitObjects(std::ifstream &file);
};

} // namespace parser::beatmap