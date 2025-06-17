#pragma once

#include <configuration/Configuration.hpp>

namespace configuration::display {

class DisplayConfiguration final : public Configuration {
  public:
    static DisplayConfiguration &getInstance();

    void load(const std::string configurationPath) override;

    int getWidth();

    int getHeight();

    void setWidth(int width);

    void setHeight(int height);

  private:
    static inline constexpr int _WIDTH = 1080;
    static inline constexpr int _HEIGHT = 720;

    int _width;
    int _height;

    DisplayConfiguration();

    ~DisplayConfiguration();

    void initialise();

    void toJson() override;
};

} // namespace configuration::display
