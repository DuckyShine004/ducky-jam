#pragma once

#include <parser/Parser.hpp>

namespace parser::beatmap {

class BeatmapParser final : public Parser {
  public:
    BeatmapParser();

    void parse(const std::string &path) override;

  private:
    nlohmann::json _hitObjects();

    void addHitObjects(std::ifstream &file);
};

} // namespace parser::beatmap