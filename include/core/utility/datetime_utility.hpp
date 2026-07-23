#pragma once

#include <string>

namespace core::utility {

class DatetimeUtility {
  public:
    static std::string get_datetime(const std::string &pattern);
};

} // namespace core::utility
