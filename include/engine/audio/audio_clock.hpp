#pragma once

#include "engine/audio/audio_source.hpp"
#include "engine/audio/audio_buffer.hpp"

namespace engine::audio {

class AudioClock {
  public:
    AudioClock(engine::audio::AudioSource &audio_source, engine::audio::AudioBuffer &audio_buffer, ALuint id);

    void start();
    void update(double delta_time);

    double track_time() const;

    engine::audio::AudioBuffer &audio_buffer();

  private:
    engine::audio::AudioSource &m_audio_source;
    engine::audio::AudioBuffer &m_audio_buffer;

    ALuint m_id;

    double m_track_speed;
    double m_track_time;
    double m_elapsed_time;

    bool m_is_running;
};

} // namespace engine::audio
