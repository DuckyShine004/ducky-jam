#pragma once

#include <string>

namespace utility::string {

class StringUtility {
  public:
    static std::string trim(std::string string);

    static bool stob(std::string string);
};

} // namespace utility::string