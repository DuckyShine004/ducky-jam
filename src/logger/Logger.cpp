#include <logger/Logger.hpp>

namespace logger {

Logger::Logger() {
}

Logger::~Logger() = default;

Logger &Logger::getInstance() {
    static Logger instance;

    return instance;
}

void Logger::log() {
}

void Logger::addEntry() {
}

void save() {
}

} // namespace logger