#include "configuration/sound/SoundConfiguration.hpp"

#include "utility/file/FileUtility.hpp"

using namespace utility::file;

namespace configuration::sound {

SoundConfiguration::SoundConfiguration() = default;

SoundConfiguration::~SoundConfiguration() = default;

SoundConfiguration &SoundConfiguration::getInstance() {
    static SoundConfiguration instance;

    return instance;
}

void SoundConfiguration::initialise() {
    FileUtility::createFile(this->_configurationPath);

    this->_scrollSpeed = this->_SCROLL_SPEED;

    this->toJson();
}

void SoundConfiguration::toJson() {
    this->_configuration["scroll_speed"] = this->_scrollSpeed;

    this->save();
}

void SoundConfiguration::toAttribute() {
    this->_scrollSpeed = this->_configuration.value("scroll_speed", this->_SCROLL_SPEED);
}

float SoundConfiguration::getScrollSpeed() {
    return this->_scrollSpeed;
}

void SoundConfiguration::setScrollSpeed(float scrollSpeed) {
    this->_scrollSpeed = scrollSpeed;

    this->toJson();
}

} // namespace configuration::sound