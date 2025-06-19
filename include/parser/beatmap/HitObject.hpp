#pragma once

namespace parser::beatmap {

class HitObject {
  public:
    HitObject(int x, int y, int type, int startTime, int endTime);

    int getLane();

    int getType();

    int getEndTime();

    int getStartTime();

    void calculateLane(int offset, int size);

  private:
    int _x;
    int _y;
    int _lane;
    int _type;
    int _endTime;
    int _startTime;
};

} // namespace parser::beatmap