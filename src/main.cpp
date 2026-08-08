#include "application/application.hpp"
#include "core/logger/logger_macros.hpp"
#include "core/platform/environment.hpp"

int main() {
    // Load application paths before anything else!
    core::platform::create_application_paths();

    application::Application application;

    if (!application.initialise()) {
        LOG_ERROR("Failed to initialise application");
        return EXIT_FAILURE;
    }

    application.load();
    application.validate();

    LOG_INFO("App data path: {}", core::platform::app_data_path().string());
    LOG_INFO("Tmp path: {}", core::platform::tmp_path().string());
    LOG_INFO("Objects path: {}", core::platform::objects_path().string());

    application.run();

    return EXIT_SUCCESS;
}
