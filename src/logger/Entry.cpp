#include <logger/Entry.hpp>

namespace logger {

Entry::Entry(Severity severity, std::string message) {
    this->_severity = severity;

    this->_message = message;

    this->_severityName = this->_SEVERITY_NAMES[static_cast<int>(severity)];
}

} // namespace logger