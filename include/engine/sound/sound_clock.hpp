#pragma once

#include "engine/sound/source.hpp"

namespace engine::sound {

class SoundClock {
  public:
    SoundClock(engine::sound::Source &source, ALuint id);

    void start();
    void update(double delta_time);

    double get_current_time();

  private:
    engine::sound::Source &m_source;

    ALuint m_id;

    double m_speed; // rate of music e.g., 0.9x, 1.05x etc.,
    double m_current_time;
    double m_elapsed_time;

    bool m_is_running;
};

} // namespace engine::sound
