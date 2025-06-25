#pragma once

#include "configuration/Configuration.hpp"

#include "engine/sound/SoundSource.hpp"

using namespace engine::sound;

namespace configuration::sound {

class SoundConfiguration final : public Configuration {
  public:
    static SoundConfiguration &getInstance();

    float getScrollSpeed();

    void setScrollSpeed(float scrollSpeed);

  private:
    static inline constexpr float _SCROLL_SPEED = 300.0f;

    float _scrollSpeed;

    SoundSource backgroundMusic;

    SoundConfiguration();

    ~SoundConfiguration();

    void initialise() override;

    void toJson() override;

    void toAttribute() override;
};

} // namespace configuration::sound