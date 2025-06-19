#include <parser/beatmap/HitObject.hpp>

namespace parser::beatmap {

HitObject::HitObject(int x, int y, int type, int startTime, int endTime) : _x(x), _y(y), _type(type), _startTime(startTime), _endTime(endTime) {};

int HitObject::getLane() {
    return this->_lane;
}

int HitObject::getType() {
    return this->_type;
}

int HitObject::getEndTime() {
    return this->_endTime;
}

int HitObject::getStartTime() {
    return this->_startTime;
}

void HitObject::calculateLane(int offset, int size) {
    this->_lane = (this->_x - offset) / size;
}

} // namespace parser::beatmap