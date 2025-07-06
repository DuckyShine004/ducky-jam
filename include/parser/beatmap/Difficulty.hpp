#pragma once

namespace parser::beatmap {

class Difficulty {
  public:
    Difficulty(float healthDrain, int lanes, float leniency);

    Difficulty();

    int getLanes();

    float getHealthDrain();

    float getLeniency();

  private:
    int _lanes;

    float _healthDrain;
    float _leniency;
};

} // namespace parser::beatmap