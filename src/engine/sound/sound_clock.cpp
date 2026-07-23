#include "engine/sound/sound_clock.hpp"

namespace engine::sound {

SoundClock::SoundClock(Source &source, ALuint id) : m_source(source), m_id(id), m_speed(1.0), m_current_time(0.0), m_elapsed_time(0.0), m_is_running(false) {
}

void SoundClock::start() {
    if (m_is_running) {
        return;
    }

    m_source.play(m_id);
    m_is_running = true;
}

void SoundClock::update(double delta_time) {
    if (!m_is_running) {
        return;
    }

    double previous_time = m_current_time;

    m_current_time = m_source.get_position();
    m_elapsed_time = m_current_time - previous_time;
}

double SoundClock::get_current_time() {
    return m_current_time;
}

} // namespace engine::sound
