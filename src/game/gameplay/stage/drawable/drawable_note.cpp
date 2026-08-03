#include "game/gameplay/stage/drawable/drawable_note.hpp"

using namespace engine::graphics::renderer;
using namespace engine::graphics::drawable;

namespace game::gameplay::stage::drawable {

DrawableNote::DrawableNote(const Note &note, const Sprite &head) : m_note(note), m_head(head) {
}

const Note &DrawableNote::note() const {
    return m_note;
}

bool DrawableNote::in_bounds(double track_time) {
    const double approach_time = 400.0f;
    const double approach_rate = (1440.0f / approach_time) / 0.75f;

    const double dy0 = m_note.y - approach_rate * track_time;
    const double dy1 = dy0 + m_note.height;

    bool out_of_bounds = (dy0 > 1440.0f || dy1 < 0.0f);

    return !out_of_bounds;
}

// offset y = y - approach_rate*current_time
void DrawableNote::update(double track_time) {
    const double approach_time = 400.0f;
    const double approach_rate = (1440.0f / approach_time) / 0.75f;

    const double offset_y = approach_rate * track_time;

    m_head.set_offset_y(-offset_y);
}

void DrawableNote::submit(Renderer &renderer) const {
    m_head.submit(renderer);
}

} // namespace game::gameplay::stage::drawable
