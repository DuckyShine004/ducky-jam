
#pragma once

#include "engine/graphic/drawable/sprite.hpp"

#include "engine/graphic/drawable/drawable.hpp"

#include "game/gameplay/stage/note.hpp"

namespace game::gameplay::stage::drawable {

class DrawableNote : public engine::graphic::drawable::Drawable {
  public:
    DrawableNote(const Note &note, const engine::graphic::drawable::Sprite &head);

    virtual bool in_bounds(double track_time);

    virtual void update(double track_time);
    virtual void submit(engine::graphic::render::Renderer &renderer) const override;

    const Note &note() const;

  protected:
    Note m_note;

    engine::graphic::drawable::Sprite m_head;
};

} // namespace game::gameplay::stage::drawable
