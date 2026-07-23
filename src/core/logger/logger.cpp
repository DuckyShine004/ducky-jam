#include <iostream>

#include "core/logger/logger.hpp"

#include "core/utility/file_utility.hpp"
#include "core/utility/datetime_utility.hpp"

using namespace core::utility;

namespace core::logger {

Logger::Logger() {
    this->initialise();
}

Logger::~Logger() = default;

Logger &Logger::get_instance() {
    static Logger *instance = new Logger();

    return *instance;
}

void Logger::initialise() {
    std::string filename = DatetimeUtility::get_datetime("%d-%m-%Y_%H-%M-%S") + ".log";

    m_log_path = ".cache/logs/" + filename;
    m_json = nlohmann::json::array();

    FileUtility::create_file(m_log_path);
}

// NOTE: Added a scoped lock. In deployment must remove lock for parallelism.
void Logger::log(Severity severity, const char *file, const char *function, int line, std::string message) {
    Entry entry(severity, file, function, line, message);

    {
        std::lock_guard<std::mutex> lock(m_log_mutex);
        this->add_entry(entry);
    }

    std::cout << entry.to_string() << std::endl;
}

void Logger::add_entry(Entry entry) {
    m_entries.push_back(entry);
    m_json.push_back(entry.get_json());

    this->save();
}

void Logger::save() {
    FileUtility::save_json(m_json, m_log_path);
}

} // namespace core::logger
