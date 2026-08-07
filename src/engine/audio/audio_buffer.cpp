#include <AL/alext.h>

#include "engine/audio/audio_buffer.hpp"

#include "core/logger/logger_macros.hpp"

namespace engine::audio {

AudioBuffer::AudioBuffer() : m_id(0), m_frames(0), m_channels(0), m_samplerate(0) {
}

AudioBuffer::~AudioBuffer() {
}

void AudioBuffer::add_audio(const std::filesystem::path &path) {
    SF_INFO audio_info{};

    const std::string path_string = path.string();
    SNDFILE *audio_file = sf_open(path_string.c_str(), SFM_READ, &audio_info);

    if (audio_file == nullptr) {
        LOG_ERROR("Could not open audio in {}: {}", path.string(), sf_strerror(audio_file));
        sf_close(audio_file);
        return;
    }

    m_frames = static_cast<std::int64_t>(audio_info.frames);
    m_channels = audio_info.channels;
    m_samplerate = audio_info.samplerate;

    ALenum format = get_audio_format(audio_file);

    if (format == AL_NONE) {
        LOG_ERROR("Unsupported channel count: {}", m_channels);
        sf_close(audio_file);
        return;
    }

    const std::size_t sample_count = static_cast<std::size_t>(audio_info.frames) * static_cast<std::size_t>(audio_info.channels);

    m_samples.resize(sample_count);

    const sf_count_t frame_count = sf_readf_float(audio_file, m_samples.data(), m_frames);

    sf_close(audio_file);

    if (frame_count <= 0) {
        LOG_ERROR("Failed to read audio file frames");
        m_samples.clear();
        return;
    }

    const std::size_t actual_sample_count = static_cast<std::size_t>(frame_count) * static_cast<std::size_t>(m_channels);

    if (actual_sample_count != sample_count) {
        m_samples.resize(actual_sample_count);
    }

    // upload audio
    ALsizei bytes = static_cast<ALsizei>(m_samples.size() * sizeof(float));

    alGenBuffers(1, &m_id);
    alBufferData(m_id, format, m_samples.data(), bytes, m_samplerate);

    if (is_openal_error()) {
        m_samples.clear();

        if (m_id != 0 && alIsBuffer(m_id)) {
            alDeleteBuffers(1, &m_id);
        }
    }
}

ALenum AudioBuffer::get_audio_format(SNDFILE *audio_file) {
    switch (m_channels) {
        case 1:
            return AL_FORMAT_MONO_FLOAT32;
        case 2:
            return AL_FORMAT_STEREO_FLOAT32;
        case 3:
            return (sf_command(audio_file, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) ? AL_FORMAT_BFORMAT2D_FLOAT32 : AL_NONE;
        case 4:
            return (sf_command(audio_file, SFC_WAVEX_GET_AMBISONIC, nullptr, 0) == SF_AMBISONIC_B_FORMAT) ? AL_FORMAT_BFORMAT3D_FLOAT32 : AL_NONE;
        default:
            return AL_NONE;
    }
}

bool AudioBuffer::is_openal_error() {
    ALenum error = alGetError();

    if (error != AL_NO_ERROR) {
        LOG_ERROR("OpenAL Error: {}", this->get_openal_error(error));
        return true;
    }

    return false;
}

const char *AudioBuffer::get_openal_error(ALenum error) {
    switch (error) {
        case AL_NO_ERROR:
            return "AL_NO_ERROR";
        case AL_INVALID_NAME:
            return "AL_INVALID_NAME";
        case AL_INVALID_ENUM:
            return "AL_INVALID_ENUM";
        case AL_INVALID_VALUE:
            return "AL_INVALID_VALUE";
        case AL_INVALID_OPERATION:
            return "AL_INVALID_OPERATION";
        case AL_OUT_OF_MEMORY:
            return "AL_OUT_OF_MEMORY";
        default:
            return "UNKNOWN_OPENAL_ERROR";
    }
}

ALuint AudioBuffer::id() const {
    return m_id;
}

std::int64_t AudioBuffer::frames() const {
    return m_frames;
}

int AudioBuffer::channels() const {
    return m_channels;
}

int AudioBuffer::samplerate() const {
    return m_samplerate;
}

std::span<const float> AudioBuffer::samples() const {
    return m_samples;
}

float AudioBuffer::samples(int index) const {
    return m_samples[index];
}

} // namespace engine::audio
