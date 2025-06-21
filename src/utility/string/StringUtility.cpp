#include <utility/string/StringUtility.hpp>

namespace utility::string {

std::string StringUtility::trim(std::string string) {
    while (!string.empty() && (string.back() == '\r' || isspace(string.back()))) {
        string.pop_back();
    }

    return string;
}

bool StringUtility::stob(std::string string) {
    return string == "1";
}

} // namespace utility::string