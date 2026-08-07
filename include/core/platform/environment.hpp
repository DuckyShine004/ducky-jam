#pragma once

#include <filesystem>

namespace core::platform {

std::filesystem::path app_data_path();
std::filesystem::path tmp_path();

inline std::filesystem::path objects_path() {
    return app_data_path() / "objects";
}

} // namespace core::platform
