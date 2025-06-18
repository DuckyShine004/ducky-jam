#include <logger/Entry.hpp>

#include <utility/datetime/DatetimeUtility.hpp>

#include <sstream>

using namespace utility::datetime;

namespace logger {

Entry::Entry(Severity severity, const char *file, const char *function, int line, std::string message) : _severity(severity), _file(file), _function(function), _line(line), _message(message) {
    int severityLevel = static_cast<int>(severity);

    this->_severityName = _NAMES[severityLevel];

    this->_backgroundColour = _BACKGROUND_COLOURS[severityLevel];

    this->_textColour = _TEXT_COLOURS[severityLevel];

    this->_date = DatetimeUtility::getDatetime("%A %d %Y");

    this->_time = DatetimeUtility::getDatetime("%H:%M:%S");

    this->_severityLevel = severityLevel;
}

std::string Entry::toString() {
    std::ostringstream oss;

    oss << _backgroundColour << _textColour << "[" << _severityName << "]" << "\033[0m";

    oss << " [" << _date << " | " << _time << "]";

    oss << " [" << _file << " | " << _function << " | " << _line << "]\n";

    oss << "  " << _message;

    return oss.str();
}

} // namespace logger