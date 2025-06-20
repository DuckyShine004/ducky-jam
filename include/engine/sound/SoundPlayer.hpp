#pragma once

#include <AL/alc.h>

#include <string>

namespace engine::sound {

class SoundPlayer {
  public:
    SoundPlayer(const SoundPlayer &) = delete;

    SoundPlayer &operator=(const SoundPlayer &) = delete;

    static SoundPlayer &getInstance();

  private:
    SoundPlayer();

    ~SoundPlayer();

    ALCdevice *_device;

    ALCcontext *_context;
};

} // namespace engine::sound