#include "core/utility/file_utility.hpp"

#include "core/exceptions/runtime_exception.hpp"

#include <fstream>
#include <sstream>

namespace core::utility {

namespace exceptions = core::exceptions;

std::string FileUtility::to_string(const std::filesystem::path &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        throw exceptions::RuntimeException("File '{}' could not be opened.", filename.string());
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

std::string FileUtility::filename(const std::filesystem::path &path) {
    return path.filename().string();
}

std::string FileUtility::basename(const std::filesystem::path &path) {
    return path.stem().string();
}

std::string FileUtility::extension(const std::filesystem::path &path) {
    return path.extension();
}

std::filesystem::path FileUtility::parent(const std::filesystem::path &path) {
    return path.parent_path();
}

bool FileUtility::exists(const std::filesystem::path &path) {
    return std::filesystem::exists(path);
}

void FileUtility::create_file(const std::filesystem::path &path) {
    if (FileUtility::exists(path)) {
        return;
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        throw exceptions::RuntimeException("File '{}' could not be opened nor could it be created.", path.string());
    }
}

void FileUtility::create_directory(const std::filesystem::path &path) {
    std::filesystem::create_directories(path);
}

std::vector<std::filesystem::path> FileUtility::children(const std::filesystem::path &parent) {
    std::vector<std::filesystem::path> children;

    for (const auto &entry : std::filesystem::directory_iterator(parent)) {
        children.emplace_back(entry);
    }

    return children;
}

bool FileUtility::is_file(const std::filesystem::path &path) {
    return std::filesystem::is_regular_file(path);
}

bool FileUtility::is_directory(const std::filesystem::path &path) {
    return std::filesystem::is_directory(path);
}

std::vector<std::string> FileUtility::split(const std::filesystem::path &path) {
    std::vector<std::string> parts;

    for (const std::filesystem::path &part : path) {
        parts.emplace_back(part.string());
    }

    return parts;
}

/* TODO: Gracefully handle the move operation */
void FileUtility::move(const std::filesystem::path &source, const std::filesystem::path &destination) {
    std::error_code error;

    std::filesystem::rename(source, destination, error);

    if (!error) {
        return;
    }

    std::filesystem::copy_file(source, destination, error);

    if (!error) {
        std::filesystem::remove(source);
    }
}

void FileUtility::clear(const std::filesystem::path &path) {
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        std::filesystem::remove_all(entry);
    }
}

} // namespace core::utility
