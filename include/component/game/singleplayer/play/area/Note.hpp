#pragma once

#include <component/Component.hpp>

namespace component::game::singleplayer::play::area {

class Note final : public Component {
  public:
    Note(float x, float y, float width, float height);

    void create() override;

    void update(float deltaTime) override;

  private:
    float _width;
    float _height;
};

} // namespace component::game::singleplayer::play::area