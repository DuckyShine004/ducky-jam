#include "configuration/skin/SkinConfiguration.hpp"

#include "utility/file/FileUtility.hpp"

using namespace utility::file;

namespace configuration::skin {

SkinConfiguration::SkinConfiguration() = default;

SkinConfiguration::~SkinConfiguration() = default;

SkinConfiguration &SkinConfiguration::getInstance() {
    static SkinConfiguration instance;

    return instance;
}

void SkinConfiguration::initialise() {
    FileUtility::createFile(this->_configurationPath);

    this->_width = this->_WIDTH;

    this->toJson();
}

void SkinConfiguration::toJson() {
    this->_configuration["width"] = this->_width;

    this->save();
}

void SkinConfiguration::toAttribute() {
    this->_width = this->_configuration.value("width", this->_WIDTH);
}

float SkinConfiguration::getWidth() {
    return this->_width;
}

} // namespace configuration::skin