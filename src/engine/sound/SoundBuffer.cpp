#include <engine/sound/SoundBuffer.hpp>

#include <logger/LoggerMacros.hpp>

#include <AL/alext.h>

#include <cstdlib>

namespace engine::sound {

SoundBuffer &SoundBuffer::getInstance() {
    static SoundBuffer instance;

    return instance;
}

SoundBuffer::SoundBuffer() {
    this->_sounds.clear();
}

SoundBuffer::~SoundBuffer() {
    alDeleteBuffers(this->_sounds.size(), this->_sounds.data());

    this->_sounds.clear();
}

ALuint SoundBuffer::addSound(const char *soundPath) {
    ALenum error;

    ALuint soundBuffer;

    SNDFILE *soundFile;

    SF_INFO soundFileInfo;

    sf_count_t frames;

    ALsizei bytes;

    short *memoryBuffer;

    if (!this->setSoundFile(soundPath, soundFile, soundFileInfo)) {
        return 0;
    }

    ALenum format;

    if (!this->setSoundFormat(format, soundFile, soundFileInfo)) {
        return 0;
    }

    memoryBuffer = this->getMemoryBuffer(soundFileInfo);

    frames = sf_readf_short(soundFile, memoryBuffer, soundFileInfo.frames);

    if (frames < 1) {
        free(memoryBuffer);

        sf_close(soundFile);

        LOG_ERROR("Failed to read samples in {} {}", soundPath, frames);

        return 0;
    }

    bytes = (ALsizei)(frames * soundFileInfo.channels) * (ALsizei)sizeof(short);

    soundBuffer = 0;

    alGenBuffers(1, &soundBuffer);
    alBufferData(soundBuffer, format, memoryBuffer, bytes, soundFileInfo.samplerate);

    free(memoryBuffer);

    sf_close(soundFile);

    error = alGetError();

    if (error != AL_NO_ERROR) {
        LOG_ERROR("OpenAL Error: {}", alGetString(error));

        if (soundBuffer && alIsBuffer(soundBuffer)) {
            alDeleteBuffers(1, &soundBuffer);
        }

        return 0;
    }

    LOG_INFO("Sound added to buffer successfully: {}", soundPath);

    this->_sounds.push_back(soundBuffer);

    return soundBuffer;
}

bool SoundBuffer::removeSound(const ALuint &sound) {
    return false;
}

short *SoundBuffer::getMemoryBuffer(const SF_INFO &soundFileInfo) {
    int channels = soundFileInfo.channels;

    sf_count_t frames = soundFileInfo.frames;

    size_t memoryBufferSize = (size_t)(frames * channels) * sizeof(short);

    return static_cast<short *>(malloc(memoryBufferSize));
}

bool SoundBuffer::setSoundFile(const char *soundPath, SNDFILE *&soundFile, SF_INFO &soundFileInfo) {
    soundFile = sf_open(soundPath, SFM_READ, &soundFileInfo);

    if (!soundFile) {
        LOG_ERROR("Could not open audio in {}: {}", soundPath, sf_strerror(soundFile));

        return false;
    }

    int channels = soundFileInfo.channels;

    sf_count_t frames = soundFileInfo.frames;

    unsigned long maxFrames = INT_MAX / (sizeof(short) * channels);

    if (frames < 1 || frames > maxFrames) {
        LOG_ERROR("Bad sample count in {} {}", soundPath, frames);

        sf_close(soundFile);

        return false;
    }

    return true;
}

bool SoundBuffer::setSoundFormat(ALenum &format, SNDFILE *soundFile, const SF_INFO &soundFileInfo) {
    int channels = soundFileInfo.channels;

    switch (channels) {
    case 1:
        format = AL_FORMAT_MONO16;

        return true;
    case 2:
        format = AL_FORMAT_STEREO16;

        return true;
    case 3:
        if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT2D_16;

            return true;
        }

        break;
    case 4:
        if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT3D_16;

            return true;
        }

        break;
    }

    format = AL_NONE;

    LOG_ERROR("Unsupported channel count: {}", channels);

    sf_close(soundFile);

    return false;
}

} // namespace engine::sound