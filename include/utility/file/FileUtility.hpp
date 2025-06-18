#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace utility::file {

class FileUtility {
  public:
    static std::string getFileToString(const std::string &filename);

    static std::string getFilenameFromPath(const std::string &path);

    static bool pathExists(const std::string &path);

    static void createFile(const std::string &path);

    static void loadJson(nlohmann::json &json, const std::string &path);

    static void saveJson(const nlohmann::json &json, const std::string &path);
};

} // namespace utility::file