#pragma once

#include <logger/Entry.hpp>

#include <string>
#include <vector>

namespace logger {

class Logger {
  public:
    Logger(const Logger &) = delete;

    Logger &operator=(const Logger &) = delete;

    static Logger &getInstance();

    void log();

    void addEntry();

    void save();

  private:
    Logger();

    ~Logger();

    std::string _logPath;

    std::vector<Entry> _entries;
};

} // namespace logger