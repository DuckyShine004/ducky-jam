#include "core/utility/datetime_utility.hpp"

#include <ctime>
#include <iomanip>
#include <sstream>

namespace core::utility {

std::string DatetimeUtility::datetime(const std::string &pattern) {
    std::time_t now = std::time(nullptr);

    std::tm time{};

    localtime_r(&now, &time);

    std::ostringstream datetime;

    datetime << std::put_time(&time, pattern.c_str());

    return datetime.str();
}

} // namespace core::utility
