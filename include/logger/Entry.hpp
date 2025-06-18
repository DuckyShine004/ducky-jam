#pragma once

#include <logger/Severity.hpp>

#include <string>

namespace logger {

class Entry {
  public:
    Entry(Severity severity, const char *file, const char *function, int line, std::string message);

    std::string toString();

  private:
    Severity _severity;

    std::string _backgroundColour;

    std::string _textColour;

    std::string _file;

    std::string _function;

    std::string _message;

    std::string _severityName;

    std::string _date;

    std::string _time;

    int _line;

    int _severityLevel;
};

} // namespace logger