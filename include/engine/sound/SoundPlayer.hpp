#pragma once

#include <engine/sound/Sound.hpp>

#include <AL/alc.h>

#include <string>

namespace engine::sound {

class SoundPlayer {
  public:
    SoundPlayer();

    void cleanup();

  private:
    Sound _music;

    ALCdevice *_device;

    ALCcontext *_context;

    void initialise();
};

} // namespace engine::sound