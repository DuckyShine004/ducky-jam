#include "game/gameplay/stage/lane.hpp"

namespace game::gameplay::stage {

namespace graphics = engine::graphics;

Lane::Lane(int lighting_frame_rate) : m_lighting_hold(lighting_frame_rate), m_lighting_normal(lighting_frame_rate), m_note_offset(0) {
}

void Lane::update(double track_time, double delta_time) {
    const double approach_time = 400.0f;
    const double approach_rate = (1440.0f / approach_time) / 0.75f;

    const double y = approach_rate * track_time;

    m_lighting_hold.update(delta_time);
    m_lighting_normal.update(delta_time);

    while (m_note_offset < m_notes.size() && m_notes[m_note_offset]->in_bounds(track_time)) {
        m_active_notes.emplace_back(m_notes[m_note_offset].get());
        ++m_note_offset;
    }

    for (drawable::DrawableNote *note : m_active_notes) {
        note->update(track_time);
    }

    std::erase_if(m_active_notes, [&](const drawable::DrawableNote *note) {
        return note->note().y + note->note().height < y;
    });
}

void Lane::add_note(std::unique_ptr<drawable::DrawableNote> note) {
    m_notes.emplace_back(std::move(note));
}

const std::vector<drawable::DrawableNote *> &Lane::active_notes() const {
    return m_active_notes;
}

graphics::animation::AnimationPlayer &Lane::lighting_hold() {
    return m_lighting_hold;
}

graphics::animation::AnimationPlayer &Lane::lighting_normal() {
    return m_lighting_normal;
}

} // namespace game::gameplay::stage
