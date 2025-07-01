#pragma once

#include "configuration/Configuration.hpp"

#include "engine/sound/SoundSource.hpp"

using namespace engine::sound;

namespace configuration::sound {

class SoundConfiguration final : public Configuration {
  public:
    static SoundConfiguration &getInstance();

    float getScrollSpeed();

    float getOffset();

    void setScrollSpeed(float scrollSpeed);

    void setOffset(float offset);

  private:
    static inline constexpr float _SCROLL_SPEED = 3000.0f;
    static inline constexpr float _OFFSET = 100.0f;

    float _scrollSpeed;
    float _offset;

    SoundSource backgroundMusic;

    SoundConfiguration();

    ~SoundConfiguration();

    void initialise() override;

    void toJson() override;

    void toAttribute() override;
};

} // namespace configuration::sound