#include "core/utility/string_utility.hpp"

#include <sstream>

namespace core::utility {

std::string StringUtility::to_upper(std::string &string) {
    std::string upper = "";

    for (char &c : string) {
        upper += std::toupper(c);
    }

    return upper;
}

// Inclusive range
std::string StringUtility::slice(const std::string &string, int start, int end) {
    int length = end - start + 1;

    return string.substr(start, length);
}

std::string StringUtility::trim(std::string string) {
    while (!string.empty() && (string.back() == '\r' || isspace(string.back()))) {
        string.pop_back();
    }

    return string;
}

std::string StringUtility::join(const std::vector<std::string> &split, const std::string &delimiter) {
    std::string result = "";

    int size = split.size();

    for (int i = 0; i < size; ++i) {
        result += split[i];

        if (i < size - 1) {
            result += delimiter;
        }
    }

    return result;
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
