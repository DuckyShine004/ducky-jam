#include "game/importer/converter.hpp"

#include "core/utility/file_utility.hpp"
#include "core/utility/string_utility.hpp"
#include "game/importer/enums/section.hpp"
#include "game/importer/parser.hpp"

#include <sstream>

namespace game::importer {

namespace utility = core::utility;

using game::importer::enums::Section;

Beatmap Converter::convert(const std::filesystem::path &path) {
    const std::string &raw_content = utility::FileUtility::to_string(path);
    const std::vector<std::string> content = get_content(raw_content);

    Parser parser;
    Section section;

    for (const std::string &line : content) {
        if (line.starts_with("[")) {
            section = get_section(line);
            continue;
        }

        // default section likely means unimplemented so we skip
        if (section == Section::Default) {
            continue;
        }

        // comment
        if (line.starts_with("//")) {
            continue;
        }

        // file format
        if (line.starts_with("osu file format")) {
            continue;
        }

        parser.parse_line(line, section);
    }

    Beatmap beatmap = parser.parse();

    return beatmap;
}

std::vector<std::string> Converter::get_content(const std::string &raw_content) {
    std::istringstream stream(raw_content);
    std::string token;
    std::vector<std::string> content;

    while (std::getline(stream, token)) {
        token = utility::StringUtility::trim(token);

        if (!token.empty()) {
            content.emplace_back(token);
        }
    }

    return content;
}

Section Converter::get_section(const std::string &line) {
    std::string section = utility::StringUtility::slice(line, 1, line.length() - 2);

    if (section == "General") {
        return Section::General;
    }

    if (section == "Metadata") {
        return Section::Metadata;
    }

    if (section == "Difficulty") {
        return Section::Difficulty;
    }

    if (section == "Events") {
        return Section::Events;
    }

    if (section == "TimingPoints") {
        return Section::TimingPoints;
    }

    if (section == "HitObjects") {
        return Section::HitObjects;
    }

    return Section::Default;
}

} // namespace game::importer
