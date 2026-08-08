#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace core::utility {

class FileUtility {
  public:
    static std::string to_string(const std::filesystem::path &filename);
    static std::string filename(const std::filesystem::path &path);
    static std::string basename(const std::filesystem::path &path);
    static std::string extension(const std::filesystem::path &path);
    static std::filesystem::path parent(const std::filesystem::path &path);
    static bool exists(const std::filesystem::path &path);

    static void create_file(const std::filesystem::path &path);
    static void create_directory(const std::filesystem::path &path);

    static std::vector<std::filesystem::path> children(const std::filesystem::path &parent);

    static bool is_file(const std::filesystem::path &path);
    static bool is_directory(const std::filesystem::path &path);

    static std::vector<std::string> split(const std::filesystem::path &path);

    static void move(const std::filesystem::path &source, const std::filesystem::path &destination);
    static void clear(const std::filesystem::path &path);
};

} // namespace core::utility
