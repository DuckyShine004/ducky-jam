#include <utility/datetime/DatetimeUtility.hpp>

#include <ctime>
#include <iomanip>
#include <sstream>

namespace utility::datetime {

std::string DatetimeUtility::getDatetime(const std::string &pattern) {
    std::time_t now = std::time(nullptr);

    std::tm time{};

    localtime_r(&now, &time);

    std::ostringstream datetime;

    datetime << std::put_time(&time, pattern.c_str());

    return datetime.str();
}

} // namespace utility::datetime