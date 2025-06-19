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
    std::vector<HitObject> _hitObjects;

    void addHitObjects(std::ifstream &file);
};

} // namespace parser::beatmap