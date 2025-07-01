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
    this->_offset = this->_OFFSET;

    this->toJson();
}

void SoundConfiguration::toJson() {
    this->_configuration["scroll_speed"] = this->_scrollSpeed;
    this->_configuration["offset"] = this->_offset;

    this->save();
}

void SoundConfiguration::toAttribute() {
    this->_scrollSpeed = this->_configuration.value("scroll_speed", this->_SCROLL_SPEED);
    this->_offset = this->_configuration.value("offset", this->_offset);
}

float SoundConfiguration::getOffset() {
    return this->_offset;
}

float SoundConfiguration::getScrollSpeed() {
    return this->_scrollSpeed;
}

void SoundConfiguration::setScrollSpeed(float scrollSpeed) {
    this->_scrollSpeed = scrollSpeed;

    this->toJson();
}

void SoundConfiguration::setOffset(float offset) {
    this->_offset = offset;

    this->toJson();
}

} // namespace configuration::sound