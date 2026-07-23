#pragma once

#include <vector>
#include <string>

#include "game/parser/beatmap.hpp"
#include "game/parser/enums/section.hpp"

namespace game::parser {

class Converter {
  public:
    static game::parser::Beatmap convert(const std::string &path);

  private:
    static std::vector<std::string> get_content(const std::string &raw_content);

    static game::parser::enums::Section get_section(const std::string &line);
};

} // namespace game::parser
