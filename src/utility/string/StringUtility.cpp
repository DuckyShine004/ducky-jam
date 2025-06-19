#include <utility/string/StringUtility.hpp>

namespace utility::string {

std::string trim(std::string string) {
    while (!string.empty() && (string.back() == '\r' || isspace(string.back()))) {
        string.pop_back();
    }

    return string;
}

} // namespace utility::string