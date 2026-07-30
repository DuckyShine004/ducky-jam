#include "engine/audio/audio_source.hpp"

namespace engine::audio {

AudioSource::AudioSource() : m_source_id(0), m_buffer_id(0) {
    alGenSources(1, &m_source_id);

    alSourcef(m_source_id, AL_GAIN, m_GAIN);
    alSourcef(m_source_id, AL_PITCH, m_PITCH);

    alSource3f(m_source_id, AL_POSITION, m_POSITION[0], m_POSITION[1], m_POSITION[2]);
    alSource3f(m_source_id, AL_VELOCITY, m_VELOCITY[0], m_VELOCITY[1], m_VELOCITY[2]);

    alSourcei(m_source_id, AL_LOOPING, m_IS_LOOPING);
    alSourcei(m_source_id, AL_BUFFER, m_buffer_id);
}

AudioSource::~AudioSource() {
    alDeleteSources(1, &m_source_id);
}

void AudioSource::play(const ALuint buffer_id) {
    if (buffer_id != m_buffer_id) {
        m_buffer_id = buffer_id;

        alSourcei(m_source_id, AL_BUFFER, (ALint)m_buffer_id);
    }

    alSourcePlay(m_source_id);
}

float AudioSource::get_position() {
    ALfloat position = 0.0f;

    alGetSourcef(m_source_id, AL_SEC_OFFSET, &position);

    return position * 1000.0f;
}

bool AudioSource::is_playing() {
    ALint state;

    alGetSourcei(m_source_id, AL_SOURCE_STATE, &state);

    return state == AL_PLAYING;
}

} // namespace engine::audio
