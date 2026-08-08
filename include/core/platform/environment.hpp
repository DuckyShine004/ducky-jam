#pragma once

#include "core/utility/file_utility.hpp"

#include <filesystem>

namespace core::platform {

std::filesystem::path app_data_path();
std::filesystem::path tmp_path();

inline std::filesystem::path objects_path() {
    return app_data_path() / "objects";
}

inline void create_application_paths() {
    utility::FileUtility::create_directory(app_data_path());
    utility::FileUtility::create_directory(tmp_path());
    utility::FileUtility::create_directory(objects_path());
}

} // namespace core::platform
