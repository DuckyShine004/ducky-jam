#pragma once

#include "engine/sound/source.hpp"

namespace engine::sound {

class SoundClock {
  public:
    SoundClock(engine::sound::Source &source, ALuint id);

    void start();
    void update(double delta_time);

    double track_time() const;

  private:
    engine::sound::Source &m_source;

    ALuint m_id;

    double m_track_speed;
    double m_track_time;
    double m_elapsed_time;

    bool m_is_running;
};

} // namespace engine::sound
