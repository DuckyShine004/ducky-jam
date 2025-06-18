#include <logger/Entry.hpp>

#include <utility/datetime/DatetimeUtility.hpp>

#include <utility/colour/ColourUtility.hpp>

#include <sstream>

using namespace utility::datetime;

using namespace utility::colour;

namespace logger {

Entry::Entry(Severity severity, const char *file, const char *function, int line, std::string message) : _severity(severity), _file(file), _function(function), _line(line), _message(message) {
    int severityLevel = static_cast<int>(severity);

    this->_severityName = _NAMES[severityLevel];

    this->_backgroundColour = ColourUtility::getAnsiBackgroundFromHex(_BACKGROUND_COLOURS[severityLevel]);

    this->_textColour = ColourUtility::getAnsiForegroundFromHex(_TEXT_COLOURS[severityLevel]);

    this->_date = DatetimeUtility::getDatetime("%A %d %Y");

    this->_time = DatetimeUtility::getDatetime("%H:%M:%S");

    this->_severityLevel = severityLevel;
}

std::string Entry::toString() {
    std::ostringstream oss;

    oss << this->_backgroundColour << this->_textColour << "[" << this->_severityName << "]" << "\033[0m";

    oss << " [" << this->_date << " | " << this->_time << "]";

    oss << " [" << this->_file << " | " << this->_function << " | " << this->_line << "]\n";

    oss << "  " << this->_message;

    return oss.str();
}

} // namespace logger