#include <sstream>

#include "core/utility/string_utility.hpp"

namespace core::utility {

std::string StringUtility::to_upper(std::string &string) {
    std::string upper = "";

    for (char &c : string) {
        upper += std::toupper(c);
    }

    return upper;
}

// Inclusive range
std::string StringUtility::slice_string(const std::string &string, int start, int end) {
    int length = end - start + 1;

    return string.substr(start, length);
}

std::string StringUtility::trim(std::string string) {
    while (!string.empty() && (string.back() == '\r' || isspace(string.back()))) {
        string.pop_back();
    }

    return string;
}

std::vector<std::string> StringUtility::split_string(const std::string &string, const char &delimiter) {
    std::vector<std::string> tokens;
    std::stringstream buffer(string);
    std::string token;

    while (std::getline(buffer, token, delimiter)) {
        tokens.push_back(token);
    }

    return tokens;
}

} // namespace core::utility
