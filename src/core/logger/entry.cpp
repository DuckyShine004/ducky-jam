#include <sstream>

#include "core/logger/entry.hpp"

#include "core/utility/file_utility.hpp"
#include "core/utility/colour_utility.hpp"
#include "core/utility/datetime_utility.hpp"

using namespace core::utility;

namespace core::logger {

Entry::Entry(Severity severity, const char *file, const char *function, int line, std::string message) : m_severity(severity), m_file(file), m_function(function), m_line(line), m_message(message) {
    int severityLevel = static_cast<int>(severity);

    m_severityName = _NAMES[severityLevel];
    m_backgroundColour = ColourUtility::get_ansi_background_from_hex(_BACKGROUND_COLOURS[severityLevel]);
    m_textColour = ColourUtility::get_ansi_foreground_from_hex(_TEXT_COLOURS[severityLevel]);
    m_date = DatetimeUtility::get_datetime("%A %d %Y");
    m_time = DatetimeUtility::get_datetime("%H:%M:%S");
    m_filename = FileUtility::get_filename_from_path(file);
    m_severityLevel = severityLevel;

    this->to_json();
}

nlohmann::json Entry::get_json() {
    return m_json;
}

std::string Entry::to_string() {
    std::ostringstream oss;

    oss << "\033[1m" << m_backgroundColour << m_textColour << "[" << m_severityName << "]" << "\033[0m";
    oss << " [" << m_date << " ~ " << m_time << "]";
    oss << " [" << m_filename << " | " << m_function << ":" << m_line << "]\n";
    oss << "  " << m_message;
    oss << '\n';

    return oss.str();
}

void Entry::to_json() {
    m_json["severity"] = m_severityName;
    m_json["level"] = m_severityLevel;
    m_json["date"] = m_date;
    m_json["time"] = m_time;
    m_json["file"] = m_file;
    m_json["function"] = m_function;
    m_json["line"] = m_line;
    m_json["message"] = m_message;
}

} // namespace core::logger
