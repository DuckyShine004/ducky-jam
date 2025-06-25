#pragma once

#include <component/Component.hpp>

namespace component::game::singleplayer::play::area {

class Note final : public Component {
  public:
    Note(float x, float width, int startTime, int endTime);

    int getStartTime();

    int getEndTime();

    glm::vec2 getSize();

    void setHeight(float height);

  private:
    int _startTime;
    int _endTime;

    glm::vec2 _size;
};

} // namespace component::game::singleplayer::play::area