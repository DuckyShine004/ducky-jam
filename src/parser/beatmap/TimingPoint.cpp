#include <parser/beatmap/TimingPoint.hpp>

namespace parser::beatmap {

TimingPoint::TimingPoint(int time, float beatLength, int meter, bool isInherited) : _time(time), _beatLength(beatLength), _meter(meter), _isInherited(isInherited) {
}

int TimingPoint::getTime() {
    return this->_time;
}

int TimingPoint::getMeter() {
    return this->_meter;
}

float TimingPoint::getBeatLength() {
    return this->_beatLength;
}

bool TimingPoint::isInherited() {
    return this->_isInherited;
}

} // namespace parser::beatmap