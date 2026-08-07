#pragma once

#include <string>
#include <vector>

#include "game/importer/beatmap.hpp"
#include "game/importer/enums/section.hpp"

namespace game::importer {

class Parser {
  public:
    Parser();

    void parse_line(const std::string &line, game::importer::enums::Section &section);
    game::importer::Beatmap parse();

  private:
    std::vector<std::string> m_general;
    std::vector<std::string> m_metadata;
    std::vector<std::string> m_difficulty;
    std::vector<std::string> m_events;
    std::vector<std::string> m_hit_objects;
    std::vector<std::string> m_timing_points;

    void parse_general(game::importer::Beatmap &beatmap);
    void parse_metadata(game::importer::Beatmap &beatmap);
    void parse_difficulty(game::importer::Beatmap &beatmap);
    void parse_events(game::importer::Beatmap &beatmap);
    void parse_timing_points(game::importer::Beatmap &beatmap);
    void parse_hit_objects(game::importer::Beatmap &beatmap);
};

} // namespace game::importer
