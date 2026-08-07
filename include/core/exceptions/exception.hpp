#pragma once

#include <exception>
#include <format>
#include <string>

namespace core::exceptions {

class Exception : public std::exception {
  public:
    template <typename... Args> explicit Exception(std::format_string<Args...> format, Args &&...args) : m_message(std::format(format, std::forward<Args>(args)...)) {
    }

    explicit Exception(const std::string &message);

    [[nodiscard]] const char *what() const noexcept override;

  private:
    std::string m_message;
};

} // namespace core::exceptions
