#pragma once

#include "AL/al.h"

namespace engine::audio {

class AudioSource {
  public:
    AudioSource();
    ~AudioSource();

    void play(const ALuint buffer_id);

    float get_position();
    float get_pitch() const;

    bool is_playing();

  private:
    static inline constexpr float m_GAIN = 1.0f;
    static inline constexpr float m_PITCH = 0.75f;

    static inline constexpr float m_POSITION[3] = {0, 0, 0};
    static inline constexpr float m_VELOCITY[3] = {0, 0, 0};

    static inline constexpr bool m_IS_LOOPING = false;

    ALuint m_source_id;
    ALuint m_buffer_id;
};

} // namespace engine::audio
