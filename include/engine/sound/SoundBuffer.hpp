#pragma once

#include <AL/al.h>

#include <vector>

namespace engine::sound {

class SoundBuffer {
  public:
    SoundBuffer(const SoundBuffer &) = delete;

    SoundBuffer &operator=(const SoundBuffer &) = delete;

    static SoundBuffer &getInstance();

    ALuint addSound(const char *soundPath);

    bool removeSound(const ALuint &sound);

  private:
    SoundBuffer();

    ~SoundBuffer();

    std::vector<ALuint> _sounds;
};

} // namespace engine::sound