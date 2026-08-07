#include "core/utility/json_utility.hpp"

#include "core/exceptions/runtime_exception.hpp"

#include <fstream>

namespace core::utility {

void JsonUtility::load(nlohmann::json &json, const std::filesystem::path &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw exceptions::RuntimeException("File '{}' could not be opened.", path.string());
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        json = nlohmann::json::object();
    } else {
        file >> json;
    }
}

void JsonUtility::save(nlohmann::json &json, const std::filesystem::path &path) {
    std::ofstream file(path);

    if (!file.is_open()) {
        throw exceptions::RuntimeException("File '{}' could not be opened.", path.string());
    }

    file << std::setw(2) << json;
}

} // namespace core::utility
