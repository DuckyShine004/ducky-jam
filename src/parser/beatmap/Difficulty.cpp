#include "parser/beatmap/Difficulty.hpp"

namespace parser::beatmap {

Difficulty::Difficulty(float healthDrain, int lanes, float leniency) : _healthDrain(healthDrain), _lanes(lanes), _leniency(leniency) {
}

Difficulty::Difficulty() = default;

int Difficulty::getLanes() {
    return this->_lanes;
}

float Difficulty::getHealthDrain() {
    return this->_healthDrain;
}

float Difficulty::getLeniency() {
    return this->_leniency;
}

} // namespace parser::beatmap