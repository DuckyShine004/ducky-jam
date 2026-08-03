
#include "game/gameplay/stage/drawable/drawable_hold_note.hpp"

using namespace engine::graphics::renderer;
using namespace engine::graphics::drawable;

namespace game::gameplay::stage::drawable {

DrawableHoldNote::DrawableHoldNote(const Note &note, const Sprite &head, const Sprite &body, const Sprite &tail) : DrawableNote(note, head), m_body(body), m_tail(tail) {
}

void DrawableHoldNote::update(double track_time) {
    const double approach_time = 400.0f;
    const double approach_rate = (1440.0f / approach_time) / 0.75f;

    const double offset_y = approach_rate * track_time;

    m_head.set_offset_y(-offset_y);
    m_body.set_offset_y(-offset_y);
    m_tail.set_offset_y(-offset_y);
}

void DrawableHoldNote::submit(Renderer &renderer) const {
    m_head.submit(renderer);
    m_body.submit(renderer);
    m_tail.submit(renderer);
}

} // namespace game::gameplay::stage::drawable
