#pragma once

#include "component/Component.hpp"

namespace component::game::singleplayer::play::area {

class Note final : public Component {
  public:
    Note(float x, float width, int startTime, int endTime, glm::vec3 colour);

    int getStartTime();

    int getEndTime();

    glm::vec2 getSize();

    glm::vec3 getColour();

    void setHeight(float height);

  private:
    int _startTime;
    int _endTime;

    glm::vec2 _size;

    glm::vec3 _colour;
};

} // namespace component::game::singleplayer::play::area