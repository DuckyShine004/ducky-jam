#include <utility/file/FileUtility.hpp>

#include <sstream>
#include <fstream>

using namespace utility::file;

std::string FileUtility::getFileToString(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        return "";
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}