#pragma once

#include <logger/Severity.hpp>

#include <string>

namespace logger {

class Entry {
  public:
    Entry(Severity severity, std::string message);

  private:
    // clang-format off
    inline static constexpr const char *_SEVERITY_NAMES[] = {
        "INFO",
        "DEBUG",
        "WARN",
        "ERROR",
        "FATAL",
    };
    // clang-format on

    Severity _severity;

    std::string _message;

    std::string _severityName;

    std::string _date;

    std::string _time;
};

} // namespace logger