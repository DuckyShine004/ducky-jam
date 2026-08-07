#include "core/exceptions/exception.hpp"

namespace core::exceptions {

Exception::Exception(const std::string &message) : m_message(message) {
}

const char *Exception::what() const noexcept {
    return m_message.c_str();
}

} // namespace core::exceptions
