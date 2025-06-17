#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace configuration {

class Configuration {
  public:
    Configuration(const Configuration &) = delete;

    Configuration &operator=(const Configuration &) = delete;

    virtual void load(const std::string configurationPath);

    virtual void save();

    nlohmann::json getConfiguration();

  protected:
    Configuration();

    ~Configuration();

    virtual void initialise() = 0;

    virtual void toJson() = 0;

    virtual void toAttribute() = 0;

    std::string _configurationPath;

    nlohmann::json _configuration;
};

} // namespace configuration