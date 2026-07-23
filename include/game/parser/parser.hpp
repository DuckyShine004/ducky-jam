#pragma once

#include <string>
#include <vector>

#include "game/parser/beatmap.hpp"
#include "game/parser/enums/section.hpp"

namespace game::parser {

class Parser {
  public:
    Parser();

    void parse_line(const std::string &line, game::parser::enums::Section &section);
    game::parser::Beatmap parse();

  private:
    std::vector<std::string> m_difficulty;
    std::vector<std::string> m_hit_objects;
    std::vector<std::string> m_timing_points;

    void parse_difficulty(game::parser::Beatmap &beatmap);
    void parse_timing_points(game::parser::Beatmap &beatmap);
    void parse_hit_objects(game::parser::Beatmap &beatmap);
};

} // namespace game::parser
