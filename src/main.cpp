#include <application/Application.hpp>

#include <engine/sound/SoundPlayer.hpp>

#include <logger/LoggerMacros.hpp>

using namespace application;

using namespace engine::sound;

int main() {
    SoundPlayer &soundPlayer = SoundPlayer::getInstance();

    Application application;

    application.initialise();

    application.load();

    application.run();

    return 0;
}