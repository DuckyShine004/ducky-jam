#pragma once

#include <string>

namespace utility {
namespace file {

class FileUtility {
  public:
    static std::string getFileToString(const std::string &filename);
};

} // namespace file
} // namespace utility