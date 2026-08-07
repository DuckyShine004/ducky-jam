#include "core/logger/logger.hpp"

#include "core/utility/datetime_utility.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/json_utility.hpp"

#include <iostream>

namespace core::logger {

namespace utility = core::utility;

Logger::Logger() {
    this->initialise();
}

Logger::~Logger() = default;

Logger &Logger::get_instance() {
    static Logger *instance = new Logger();

    return *instance;
}

void Logger::initialise() {
    std::string filename = utility::DatetimeUtility::datetime("%d-%m-%Y_%H-%M-%S") + ".log";

    m_log_path = std::filesystem::path(".cache/logs") / filename;
    m_json = nlohmann::json::array();

    utility::FileUtility::create_directory(m_log_path.parent_path());
    utility::FileUtility::create_file(m_log_path);
}

// NOTE: Added a scoped lock. In deployment must remove lock for parallelism.
void Logger::log(Severity severity, const char *file, const char *function, int line, std::string message) {
    Entry entry(severity, file, function, line, message);

    {
        std::lock_guard<std::mutex> lock(m_log_mutex);
        add_entry(entry);
    }

    std::cout << entry.to_string() << std::endl;
}

void Logger::add_entry(Entry entry) {
    m_entries.push_back(entry);
    m_json.push_back(entry.get_json());

    this->save();
}

void Logger::save() {
    utility::JsonUtility::save(m_json, m_log_path);
}

} // namespace core::logger
