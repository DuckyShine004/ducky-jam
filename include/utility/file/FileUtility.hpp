#pragma once

#include <string>

namespace utility::file {

class FileUtility {
  public:
    static std::string getFileToString(const std::string &filename);
};

} // namespace utility::file