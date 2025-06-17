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

    void log(Severity severity, std::string message);

    void addEntry(Severity severity, std::string message);

    void save();

  private:
    Logger();

    ~Logger();

    void initialise();

    std::string _logPath;

    std::vector<Entry> _entries;
};

} // namespace logger