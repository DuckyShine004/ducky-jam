#include <cmath>

#include "engine/sound/sound_clock.hpp"

namespace engine::sound {

SoundClock::SoundClock(Source &source, ALuint id) : m_source(source), m_id(id), m_track_speed(0.75f), m_track_time(0.0f), m_elapsed_time(0.0f), m_is_running(false) {
}

void SoundClock::start() {
    if (m_is_running) {
        return;
    }

    m_source.play(m_id);
    m_is_running = true;
}

// Smooth note update: https://github.com/ppy/osu
// https://github.com/InventiveRhythm/fluXis
void SoundClock::update(double delta_time) {
    if (!m_is_running)
        return;

    const double delta_ms = delta_time * 1000.0f;

    m_track_time += delta_ms * m_track_speed;

    const double audioTime = m_source.get_position();
    const double error = audioTime - m_track_time;

    constexpr double snap_threshold_ms = 33.0f;
    constexpr double recovery_ms = 50.0f;

    if (std::abs(error) > snap_threshold_ms) {
        m_track_time = audioTime;
    } else {
        const double correction = 1.0f - std::exp2(-delta_ms / recovery_ms);

        m_track_time += error * correction;
    }
}

double SoundClock::track_time() const {
    return m_track_time;
}

} // namespace engine::sound
