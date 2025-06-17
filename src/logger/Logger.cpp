#include <logger/Logger.hpp>

#include <utility/file/FileUtility.hpp>

#include <utility/datetime/DatetimeUtility.hpp>

using namespace utility::file;

using namespace utility::datetime;

namespace logger {

Logger::Logger() {
    this->initialise();
}

Logger::~Logger() = default;

Logger &Logger::getInstance() {
    static Logger instance;

    return instance;
}

void Logger::initialise() {
    std::string filename = DatetimeUtility::getDatetime("%d-%m-%Y:%H-%M-%S") + ".log";

    this->_logPath = ".config/" + filename;

    FileUtility::createFile(this->_logPath);
}

void Logger::log(Severity severity, std::string message) {
    this->addEntry(severity, message);
}

void Logger::addEntry(Severity severity, std::string message) {
    Entry entry(severity, message);

    this->_entries.push_back(entry);
}

void save() {
}

} // namespace logger