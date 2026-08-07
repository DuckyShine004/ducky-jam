
#pragma once

#include <format>
#include <stdexcept>

namespace core::exceptions {

class InvalidArgumentException : public std::invalid_argument {
  public:
    template <typename... Args> explicit InvalidArgumentException(std::format_string<Args...> format, Args &&...args) : std::invalid_argument(std::format(format, std::forward<Args>(args)...)) {
    }
};

} // namespace core::exceptions
