#pragma once

#include <nlohmann/json.hpp>

#include <filesystem>

namespace core::utility {

class JsonUtility {
  public:
    static void load(nlohmann::json &json, const std::filesystem::path &path);
    static void save(nlohmann::json &json, const std::filesystem::path &path);
};

} // namespace core::utility
