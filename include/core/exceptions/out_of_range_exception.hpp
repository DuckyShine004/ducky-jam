#pragma once

#include <format>
#include <stdexcept>

namespace core::exceptions {

class OutOfRangeException : public std::out_of_range {
  public:
    template <typename... Args> explicit OutOfRangeException(std::format_string<Args...> format, Args &&...args) : std::out_of_range(std::format(format, std::forward<Args>(args)...)) {
    }
};

} // namespace core::exceptions
