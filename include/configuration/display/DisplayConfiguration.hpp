#pragma once

#include <configuration/Configuration.hpp>

namespace configuration::display {

class DisplayConfiguration final : public Configuration {
  public:
    static DisplayConfiguration &getInstance();

    int getWidth();

    int getHeight();

    void setWidth(int width);

    void setHeight(int height);

    void updateResolution(int width, int height);

  private:
    static inline constexpr int _WIDTH = 1080;
    static inline constexpr int _HEIGHT = 720;

    int _width;
    int _height;

    DisplayConfiguration();

    ~DisplayConfiguration();

    void initialise() override;

    void toJson() override;

    void toAttribute() override;
};

} // namespace configuration::display
