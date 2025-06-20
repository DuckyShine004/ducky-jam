#include <engine/sound/SoundPlayer.hpp>

namespace engine::sound {

SoundPlayer::SoundPlayer() {
    this->initialise();
}

void SoundPlayer::initialise() {
    const ALCchar *deviceName = alcGetString(0, ALC_DEFAULT_DEVICE_SPECIFIER);

    this->_device = alcOpenDevice(deviceName);

    this->_context = alcCreateContext(this->_device, nullptr);

    alcMakeContextCurrent(this->_context);
}

void SoundPlayer::cleanup() {
    alcDestroyContext(this->_context);

    alcCloseDevice(this->_device);
}

} // namespace engine::sound