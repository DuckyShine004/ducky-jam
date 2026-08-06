#include <fmt/format.h>
#include <stack>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <unordered_set>

#include <openssl/evp.h>

#include "core/utility/file_utility.hpp"
#include "core/utility/string_utility.hpp"

#include "core/logger/logger_macros.hpp"

namespace core::utility {

std::string FileUtility::get_file_to_string(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);

    if (!file.is_open()) {
        LOG_ERROR("File '{}' could not be opened", filename);
        std::terminate();
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();
}

std::string FileUtility::get_filename_from_path(const std::string &path) {
    std::filesystem::path full_path(path);

    std::string filename = full_path.filename().string();

    return filename;
}

std::string FileUtility::get_basename_from_path(const std::string &path) {
    std::filesystem::path full_path(path);

    std::string basename = full_path.stem().string();

    return basename;
}

std::string FileUtility::get_extension(const std::string &path) {
    std::filesystem::path full_path(path);

    std::string extension = full_path.extension();

    return extension;
}

std::string FileUtility::get_parent_directory(const std::string &path) {
    std::filesystem::path full_path(path);

    std::string parent_directory = full_path.parent_path().string();

    return parent_directory;
}

// WARN: WE ASSUME THAT ONLY COMPUTE SHADER FILES CAN ONLY HAVE INCLUDES, SETTING UP PRAGMA WOULD BE TRICKY
std::string FileUtility::get_shader_file(const std::string &path) {
    LOG_INFO("Parsing shader file '{}'", path);

    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        LOG_ERROR("File '{}' could not be opened", path);
        std::terminate();
    }

    std::string parent_directory = FileUtility::get_parent_directory(path);

    std::string token;

    std::stringstream buffer;

    std::unordered_set<std::string> includes;

    int line = 0;

    while (std::getline(file, token)) {
        ++line;

        if (token.starts_with("#include")) {
            std::string include_path_raw = StringUtility::split_string(token, ' ')[1];

            std::string include_path = StringUtility::slice_string(include_path_raw, 1, include_path_raw.length() - 2);

            std::string full_include_path = parent_directory + '/' + include_path;

            if (includes.find(full_include_path) != includes.end()) {
                LOG_WARN("Skipping include '{}' at line {}", full_include_path, line);
                continue;
            }

            std::string include_source = FileUtility::get_file_to_string(full_include_path);

            includes.insert(full_include_path);

            buffer << include_source << '\n';
        } else if (token.starts_with("#extension")) {
            std::string extension = StringUtility::split_string(token, ' ')[1];

            if (extension == "GL_GOOGLE_include_directive") {
                continue;
            }
        } else {
            buffer << token << '\n';
        }
    }

    // LOG_DEBUG("Buffer: {}", buffer.str());

    return buffer.str();
}

bool FileUtility::path_exists(const std::string &path) {
    return std::filesystem::exists(path);
}

void FileUtility::create_file(const std::string &path) {
    if (FileUtility::path_exists(path)) {
        LOG_INFO("File '{}' already exists, skipping...", path);
        return;
    }

    std::ofstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to open or create the file: " + path);
    }
}

void FileUtility::load_json(nlohmann::json &json, const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Failed to open the file: " + path);
        return;
    }

    if (file.peek() == std::ifstream::traits_type::eof()) {
        json = nlohmann::json::object();
    } else {
        file >> json;
    }
}

void FileUtility::save_json(const nlohmann::json &json, const std::string &path) {
    std::ofstream file(path);

    if (!file.is_open()) {
        return;
    }

    file << std::setw(2) << json;
}

// NOTE: Assume starts with name/
std::vector<std::string> FileUtility::get_files_in_directory(std::string directory) {
    std::vector<std::string> files;

    std::stack<std::string> directories;

    directories.push(directory);

    while (!directories.empty()) {
        std::string directory = directories.top();

        directories.pop();

        if (!FileUtility::path_exists(directory)) {
            continue;
        }

        std::vector<std::string> paths_in_directory = FileUtility::get_paths_in_directory(directory);

        for (std::string path : paths_in_directory) {
            if (FileUtility::is_file(path)) {
                files.push_back(path);
            } else if (FileUtility::is_directory(path)) {
                directories.push(path);
            }
        }
    }

    return files;
}

std::vector<std::string> FileUtility::get_paths_in_directory(std::string directory) {
    std::vector<std::string> paths;

    for (const auto &entry : std::filesystem::directory_iterator(directory)) {
        paths.push_back(entry.path().string());
    }

    return paths;
}

bool FileUtility::is_file(const std::string &path) {
    return std::filesystem::is_regular_file(path);
}

bool FileUtility::is_directory(const std::string &path) {
    return std::filesystem::is_directory(path);
}

int FileUtility::get_number_of_files_in_directory(const std::string &directory, const std::regex &pattern) {
    std::vector<std::string> files = FileUtility::get_files_in_directory(directory);

    int number_of_files = 0;

    for (std::string &file : files) {
        if (std::regex_match(file, pattern)) {
            ++number_of_files;
        }
    }

    return number_of_files;
}

void FileUtility::clear_directory(const std::string &directory) {
    std::filesystem::path filepath(directory);

    for (const auto &entry : std::filesystem::directory_iterator(filepath)) {
        std::filesystem::remove_all(entry);
    }
}

std::string FileUtility::hash_file(const std::string &path) {
    std::ifstream file(path, std::ios::binary);

    std::unique_ptr<EVP_MD_CTX, void (*)(EVP_MD_CTX *)> context(EVP_MD_CTX_new(), EVP_MD_CTX_free);

    if (!context) {
        throw std::runtime_error("Failed to create OpenSSL context");
    }

    if (EVP_DigestInit_ex(context.get(), EVP_sha256(), nullptr) != 1) {
        throw std::runtime_error("Failed to initialize SHA-256 digest");
    }

    // use 4kb for now
    constexpr std::size_t buffer_size = 4096;
    std::vector<char> buffer(4096);

    while (file.read(buffer.data(), buffer_size) || file.gcount() > 0) {
        if (EVP_DigestUpdate(context.get(), buffer.data(), file.gcount()) != 1) {
            throw std::runtime_error("Failed to update SHA-256 digest");
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length = 0;

    if (EVP_DigestFinal_ex(context.get(), hash, &hash_length) != 1) {
        throw std::runtime_error("Failed to finalize SHA-256 digest");
    }

    std::stringstream hex_stream;

    for (int i = 0; i < hash_length; ++i) {
        hex_stream << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }

    return hex_stream.str();
}

void FileUtility::move_file(const std::string &source, const std::string &target) {
    std::filesystem::rename(source, target);
}

} // namespace core::utility
