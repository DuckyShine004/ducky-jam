#pragma once

#include <string>

#include <nlohmann/json.hpp>

#include "core/logger/severity.hpp"

namespace core::logger {

class Entry {
  public:
    Entry(core::logger::Severity severity, const char *file, const char *function, int line, std::string message);

    nlohmann::json get_json();
    std::string to_string();

  private:
    void to_json();

    core::logger::Severity m_severity;

    nlohmann::json m_json;

    std::string m_backgroundColour;
    std::string m_textColour;
    std::string m_file;
    std::string m_filename;
    std::string m_function;
    std::string m_message;
    std::string m_severityName;
    std::string m_date;
    std::string m_time;

    int m_line;
    int m_severityLevel;
};

} // namespace core::logger
