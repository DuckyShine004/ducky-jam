#include <configuration/Configuration.hpp>

#include <utility/file/FileUtility.hpp>

using namespace utility::file;

namespace configuration {

Configuration::Configuration() = default;

Configuration::~Configuration() = default;

void Configuration::load(const std::string configurationPath) {
    this->_configurationPath = configurationPath;

    if (!FileUtility::pathExists(configurationPath)) {
        this->initialise();

        return;
    }

    FileUtility::loadJson(this->_configuration, configurationPath);

    this->toAttribute();
}

void Configuration::save() {
    this->toJson();

    FileUtility::saveJson(this->_configuration, this->_configurationPath);
}

nlohmann::json Configuration::getConfiguration() {
    return this->_configuration;
}

} // namespace configuration