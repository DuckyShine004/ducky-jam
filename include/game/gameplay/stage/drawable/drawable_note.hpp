
#pragma once

#include "engine/graphics/drawable/sprite.hpp"

#include "engine/graphics/drawable/drawable.hpp"

#include "game/gameplay/stage/note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableNote : public engine::graphics::drawable::Drawable {
  public:
    DrawableNote(const Note &note, const engine::graphics::drawable::Sprite &head);

    virtual bool in_bounds(double track_time);

    virtual void update(double track_time);
    virtual void submit(engine::graphics::renderer::Renderer &renderer) const override;

    const Note &note() const;

  protected:
    Note m_note;

    engine::graphics::drawable::Sprite m_head;
};

} // namespace game::gameplay::stage::drawable
