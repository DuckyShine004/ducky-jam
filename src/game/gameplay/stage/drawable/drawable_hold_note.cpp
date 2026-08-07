
#include "game/gameplay/stage/drawable/drawable_hold_note.hpp"

namespace game::gameplay::stage::drawable {

namespace graphics = engine::graphics;

DrawableHoldNote::DrawableHoldNote(const Note &note, const graphics::drawable::Sprite &head, const graphics::drawable::Sprite &body, const graphics::drawable::Sprite &tail) : DrawableNote(note, head), m_body(body), m_tail(tail) {
}

void DrawableHoldNote::update(double track_time) {
    const double approach_time = 400.0f;
    const double approach_rate = (1440.0f / approach_time) / 0.75f;

    const double offset_y = approach_rate * track_time;

    m_head.set_offset_y(-offset_y);
    m_body.set_offset_y(-offset_y);
    m_tail.set_offset_y(-offset_y);
}

void DrawableHoldNote::submit(graphics::renderer::Renderer &renderer) const {
    m_head.submit(renderer);
    m_body.submit(renderer);
    m_tail.submit(renderer);
}

} // namespace game::gameplay::stage::drawable
