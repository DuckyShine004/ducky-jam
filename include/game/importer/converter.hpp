#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "game/importer/beatmap.hpp"
#include "game/importer/enums/section.hpp"

namespace game::importer {

class Converter {
  public:
    static game::importer::Beatmap convert(const std::filesystem::path &path);

  private:
    static std::vector<std::string> get_content(const std::string &raw_content);

    static game::importer::enums::Section get_section(const std::string &line);
};

} // namespace game::importer
