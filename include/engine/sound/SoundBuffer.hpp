#pragma once

#include <AL/al.h>

#include <sndfile.h>

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

    short *getMemoryBuffer(const SF_INFO &soundFileInfo);

    bool setSoundFile(const char *soundPath, SNDFILE *&soundFile, SF_INFO &soundFileInfo);

    bool setSoundFormat(ALenum &format, SNDFILE *soundFile, const SF_INFO &soundFileInfo);

    std::vector<ALuint> _sounds;
};

} // namespace engine::sound