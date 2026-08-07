#pragma once

#include <filesystem>
#include <string>

namespace core::utility {

class HashUtility {
  public:
    static std::string hash_file(const std::filesystem::path &path);
};

} // namespace core::utility
