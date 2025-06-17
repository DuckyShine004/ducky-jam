#include <configuration/display/DisplayConfiguration.hpp>

#include <utility/file/FileUtility.hpp>

using namespace utility::file;

namespace configuration::display {

DisplayConfiguration::DisplayConfiguration() = default;

DisplayConfiguration::~DisplayConfiguration() = default;

DisplayConfiguration &DisplayConfiguration::getInstance() {
    static DisplayConfiguration instance;

    return instance;
}

void DisplayConfiguration::initialise() {
    FileUtility::createFile(this->_configurationPath);

    this->_width = this->_WIDTH;
    this->_height = this->_HEIGHT;

    this->toJson();

    this->save();
}

void DisplayConfiguration::load(const std::string configurationPath) {
    this->_configurationPath = configurationPath;

    if (FileUtility::pathExists(configurationPath)) {
        this->initialise();

        return;
    }

    FileUtility::loadJson(this->_configuration, configurationPath);

    this->toAttribute();
}

void DisplayConfiguration::toJson() {
    this->_configuration["width"] = this->_width;
    this->_configuration["height"] = this->_height;
}

void DisplayConfiguration::toAttribute() {
    this->_width = this->_configuration.value("width", this->_WIDTH);
    this->_height = this->_configuration.value("height", this->_HEIGHT);
}

int DisplayConfiguration::getWidth() {
    return this->_width;
}

int DisplayConfiguration::getHeight() {
    return this->_height;
}

void DisplayConfiguration::setWidth(int width) {
    this->_width = width;

    this->toJson();
}

void DisplayConfiguration::setHeight(int height) {
    this->_height = height;

    this->toJson();
}

} // namespace configuration::display