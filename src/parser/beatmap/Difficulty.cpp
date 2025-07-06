#include "parser/beatmap/Difficulty.hpp"

namespace parser::beatmap {

Difficulty::Difficulty(int healthDrain, int lanes, int leniency) : _healthDrain(healthDrain), _lanes(lanes), _leniency(leniency) {
}

Difficulty::Difficulty() = default;

int Difficulty::getLanes() {
    return this->_lanes;
}

int Difficulty::getHealthDrain() {
    return this->_healthDrain;
}

int Difficulty::getLeniency() {
    return this->_leniency;
}

} // namespace parser::beatmap