#include <utility/file/FileUtility.hpp>

#include <sstream>
#include <fstream>
#include <filesystem>

namespace utility::file {

std::string FileUtility::getFileToString(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

std::string FileUtility::getFilenameFromPath(const std::string &path) {
    std::filesystem::path fullPath(path);

    std::string filename = fullPath.filename().string();

    return filename;
}

bool FileUtility::pathExists(const std::string &path) {
    return std::filesystem::exists(path);
}

void FileUtility::createFile(const std::string &path) {
    if (FileUtility::pathExists(path)) {
        return;
    }

    std::ofstream(path).close();
}

void FileUtility::loadJson(nlohmann::json &json, const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        return;
    }

    file >> json;
}

void FileUtility::saveJson(const nlohmann::json &json, const std::string &path) {
    std::ofstream file(path);

    if (!file.is_open()) {
        return;
    }

    file << std::setw(2) << json;
}

} // namespace utility::file