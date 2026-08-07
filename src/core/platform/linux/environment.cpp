#include "core/platform/environment.hpp"

#include "core/config/app_config.hpp"
#include "core/exceptions/runtime_exception.hpp"

namespace core::platform {

std::filesystem::path app_data_path() {
    if (const char *xdg_data_home = std::getenv("XDG_DATA_HOME")) {
        return std::filesystem::path(xdg_data_home) / core::config::application_name;
    }

    if (const char *home = std::getenv("HOME")) {
        return std::filesystem::path(home) / ".local/share" / core::config::application_name;
    }

    throw core::exceptions::RuntimeException("Unable to determine application data path");
}

std::filesystem::path tmp_path() {
    return std::filesystem::temp_directory_path();
}

} // namespace core::platform
