#include <engine/sound/SoundPlayer.hpp>

namespace engine::sound {

SoundPlayer &SoundPlayer::getInstance() {
    static SoundPlayer instance;

    return instance;
}

SoundPlayer::SoundPlayer() {
    const ALCchar *deviceName = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);

    this->_device = alcOpenDevice(deviceName);

    this->_context = alcCreateContext(this->_device, nullptr);

    alcMakeContextCurrent(this->_context);
}

SoundPlayer::~SoundPlayer() {
    alcMakeContextCurrent(nullptr);

    alcDestroyContext(this->_context);

    alcCloseDevice(this->_device);
};

} // namespace engine::sound