#pragma once

#include "AL/al.h"

namespace engine::audio {

class AudioSource {
  public:
    AudioSource();
    ~AudioSource();

    void initialise();

    void play(const ALuint buffer_id);

    float get_position();
    float get_pitch() const;

    bool playing();
    bool reserved();

    void set_reserved(bool state);

  private:
    static inline constexpr float default_gain = 1.0f;
    static inline constexpr float default_pitch = 1.0f;

    static inline constexpr float default_position[3] = {0, 0, 0};
    static inline constexpr float default_velocity[3] = {0, 0, 0};

    static inline constexpr bool looping = false;

    ALuint m_source_id;
    ALuint m_buffer_id;

    bool m_reserved;
};

} // namespace engine::audio
