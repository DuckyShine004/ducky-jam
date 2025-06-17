#include <application/Application.hpp>

using namespace application;

int main() {
    Application application;

    application.initialise();

    application.load();

    application.run();

    return 0;
}