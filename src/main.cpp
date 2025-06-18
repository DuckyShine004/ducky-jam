#include <application/Application.hpp>

#include <logger/LoggerMacros.hpp>

using namespace application;

int main() {
    LOG_INFO("BRUH {}", "jsdfjl");
    LOG_DEBUG("BRUH {}", "jsdfjl");
    LOG_WARN("BRUH {}", "jsdfjl");
    LOG_ERROR("BRUH {}", "jsdfjl");
    LOG_FATAL("BRUH {}", "jsdfjl");
    Application application;

    application.initialise();

    application.load();

    application.run();

    return 0;
}