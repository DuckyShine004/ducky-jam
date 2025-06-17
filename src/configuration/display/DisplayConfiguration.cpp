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
}

void DisplayConfiguration::load(const std::string configurationPath) {
    this->_configurationPath = configurationPath;

    if (FileUtility::pathExists(configurationPath)) {
        this->initialise();

        return;
    }

    FileUtility::loadJson(this->_configuration, configurationPath);

    this->_width = this->_configuration["width"];
    this->_height = this->_configuration["height"];
}

void DisplayConfiguration::save() {
    this->toJson();

    FileUtility::saveJson(this->_configuration, this->_configurationPath);
}

void DisplayConfiguration::toJson() {
    this->_configuration["width"] = this->_width;
    this->_configuration["height"] = this->_height;
}

} // namespace configuration::display