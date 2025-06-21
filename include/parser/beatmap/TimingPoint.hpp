#pragma once

namespace parser::beatmap {

class TimingPoint {
    TimingPoint(int time, float beatLength, int meter, bool isInherited);

    int getTime();

    int getMeter();

    float getBeatLength();

    bool isInherited();

  private:
    int _time;
    int _meter;

    float _beatLength;

    bool _isInherited;
};

} // namespace parser::beatmap