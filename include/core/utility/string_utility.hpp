#pragma once

#include <glm/glm.hpp>
#include <string>

namespace core::utility {

class StringUtility {
  public:
    static std::string to_upper(std::string &string);
    static std::string slice(const std::string &string, int start, int end);
    static std::string trim(std::string string);
    static std::string join(const std::vector<std::string> &split, const std::string &delimeter = "");

    static std::vector<std::string> split_string(const std::string &string, const char &delimiter);
};

} // namespace core::utility
