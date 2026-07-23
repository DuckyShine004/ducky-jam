#include <sstream>

#include "game/parser/parser.hpp"
#include "game/parser/converter.hpp"
#include "game/parser/enums/section.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/string_utility.hpp"

using namespace core::logger;
using namespace core::utility;

namespace game::parser {

using game::parser::enums::Section;

Beatmap Converter::convert(const std::string &path) {
    const std::string &raw_content = FileUtility::get_file_to_string(path);
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
        token = StringUtility::trim(token);

        if (!token.empty()) {
            content.emplace_back(token);
        }
    }

    return content;
}

Section Converter::get_section(const std::string &line) {
    std::string section = StringUtility::slice_string(line, 1, line.length() - 2);

    if (section == "Difficulty") {
        return Section::Difficulty;
    }

    if (section == "TimingPoints") {
        return Section::TimingPoints;
    }

    if (section == "HitObjects") {
        return Section::HitObjects;
    }

    return Section::Default;
}

} // namespace game::parser
