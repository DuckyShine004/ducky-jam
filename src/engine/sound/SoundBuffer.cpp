#include <engine/sound/SoundBuffer.hpp>

#include <logger/LoggerMacros.hpp>

#include <AL/alext.h>

#include <sndfile.h>

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
    ALenum format;

    ALuint soundBuffer;

    SNDFILE *soundFile;

    SF_INFO soundFileInfo;

    sf_count_t frames;

    ALsizei bytes;

    short *memoryBuffer;

    soundFile = sf_open(soundPath, SFM_READ, &soundFileInfo);

    if (!soundFile) {
        LOG_ERROR("Could not open audio in {}: {}", soundPath, sf_strerror(soundFile));

        return 0;
    }

    if (soundFileInfo.frames < 1 || soundFileInfo.frames > (sf_count_t)(INT_MAX / sizeof(short)) / soundFileInfo.channels) {
        LOG_ERROR("Bad sample count in {} {}", soundPath, soundFileInfo.frames);

        sf_close(soundFile);

        return 0;
    }

    format = AL_NONE;

    if (soundFileInfo.channels == 1) {
        format = AL_FORMAT_MONO16;
    } else if (soundFileInfo.channels == 2) {
        format = AL_FORMAT_STEREO16;
    } else if (soundFileInfo.channels == 3) {
        if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT2D_16;
        }
    } else if (soundFileInfo.channels == 4) {
        if (sf_command(soundFile, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) {
            format = AL_FORMAT_BFORMAT3D_16;
        }
    }

    if (!format) {
        LOG_ERROR("Unsupported channel count: {}", soundFileInfo.channels);

        sf_close(soundFile);

        return 0;
    }

    memoryBuffer = static_cast<short *>(malloc((size_t)(soundFileInfo.frames * soundFileInfo.channels) * sizeof(short)));

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

} // namespace engine::sound