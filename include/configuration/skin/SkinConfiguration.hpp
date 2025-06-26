#pragma once

#include "configuration/Configuration.hpp"

namespace configuration::skin {

class SkinConfiguration final : public Configuration {
  public:
    static SkinConfiguration &getInstance();

    float getWidth();

  private:
    static inline constexpr float _WIDTH = 128.0f;

    float _width;

    SkinConfiguration();

    ~SkinConfiguration();

    void initialise() override;

    void toJson() override;

    void toAttribute() override;
};

} // namespace configuration::skin