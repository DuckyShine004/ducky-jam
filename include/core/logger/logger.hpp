#pragma once

#include <mutex>
#include <filesystem>
#include <string>
#include <vector>

#include "core/logger/entry.hpp"

namespace core::logger {

class Logger {
  public:
    Logger(const core::logger::Logger &) = delete;
    Logger &operator=(const core::logger::Logger &) = delete;

    static Logger &get_instance();

    void log(core::logger::Severity severity, const char *file, const char *function, int line, std::string message);
    void add_entry(core::logger::Entry entry);
    void save();

  private:
    Logger();
    ~Logger();

    void initialise();
    void run();

    std::mutex m_log_mutex;

    nlohmann::json m_json;

    std::vector<core::logger::Entry> m_entries;

    std::filesystem::path m_log_path;
};

} // namespace core::logger
