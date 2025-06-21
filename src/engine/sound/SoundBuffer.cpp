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
    SNDFILE *soundFile;

    SF_INFO soundFileInfo;

    if (!this->setSoundFile(soundPath, soundFile, soundFileInfo)) {
        return 0;
    }

    ALenum format;

    if (!this->setSoundFormat(format, soundFile, soundFileInfo)) {
        return 0;
    }

    short *memoryBuffer = this->getMemoryBuffer(soundFileInfo);

    sf_count_t numberOfFrames;

    if (!this->setNumberOfFrames(numberOfFrames, soundFile, soundFileInfo, memoryBuffer)) {
        return 0;
    }

    ALuint soundBuffer;

    if (!this->setSoundBuffer(soundBuffer, soundFile, soundFileInfo, format, numberOfFrames, memoryBuffer)) {
        return 0;
    }

    if (this->isSoundError(soundBuffer)) {
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

bool SoundBuffer::setNumberOfFrames(sf_count_t &numberOfFrames, SNDFILE *soundFile, const SF_INFO &soundFileInfo, short *memoryBuffer) {
    numberOfFrames = sf_readf_short(soundFile, memoryBuffer, soundFileInfo.frames);

    if (numberOfFrames < 1) {
        free(memoryBuffer);

        sf_close(soundFile);

        LOG_ERROR("Failed to read sound file frames");

        return false;
    }

    return true;
}

bool SoundBuffer::setSoundBuffer(ALuint &soundBuffer, SNDFILE *soundFile, const SF_INFO &soundFileInfo, ALenum &format, sf_count_t &numberOfFrames, short *memoryBuffer) {
    ALsizei numberOfBytes = (ALsizei)(numberOfFrames * soundFileInfo.channels) * (ALsizei)sizeof(short);

    soundBuffer = 0;

    alGenBuffers(1, &soundBuffer);
    alBufferData(soundBuffer, format, memoryBuffer, numberOfBytes, soundFileInfo.samplerate);

    free(memoryBuffer);

    sf_close(soundFile);

    return true;
}

bool SoundBuffer::isSoundError(ALuint soundBuffer) {
    ALenum error = alGetError();

    if (error != AL_NO_ERROR) {
        LOG_ERROR("OpenAL Error: {}", alGetString(error));

        if (soundBuffer && alIsBuffer(soundBuffer)) {
            alDeleteBuffers(1, &soundBuffer);
        }

        return true;
    }

    return false;
}

} // namespace engine::sound