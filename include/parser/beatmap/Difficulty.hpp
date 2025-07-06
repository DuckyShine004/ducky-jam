#pragma once

namespace parser::beatmap {

class Difficulty {
  public:
    Difficulty(int healthDrain, int lanes, int leniency);

    Difficulty();

    int getLanes();

    int getHealthDrain();

    int getLeniency();

  private:
    int _healthDrain;
    int _lanes;
    int _leniency;
};

} // namespace parser::beatmap