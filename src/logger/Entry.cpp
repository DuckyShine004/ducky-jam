#include <logger/Entry.hpp>

#include <utility/datetime/DatetimeUtility.hpp>

using namespace utility::datetime;

namespace logger {

Entry::Entry(Severity severity, std::string message) : _severity(severity), _message(message) {
    this->_severityName = this->_SEVERITY_NAMES[static_cast<int>(severity)];

    this->_date = DatetimeUtility::getDatetime("%A %d %Y");

    this->_time = DatetimeUtility::getDatetime("%H:%M:%S");
}

} // namespace logger