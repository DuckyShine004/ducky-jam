#pragma once

#include <format>
#include <stdexcept>

namespace core::exceptions {

class RuntimeException : public std::runtime_error {
  public:
    template <typename... Args> explicit RuntimeException(std::format_string<Args...> format, Args &&...args) : std::runtime_error(std::format(format, std::forward<Args>(args)...)) {
    }
};

} // namespace core::exceptions
