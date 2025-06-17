#pragma once

#include <string>

#include <nlohmann/json.hpp>

namespace configuration {

class Configuration {
  public:
    Configuration(const Configuration &) = delete;

    Configuration &operator=(const Configuration &) = delete;

    virtual void load(const std::string configurationPath) = 0;

    virtual void save() = 0;

  protected:
    Configuration();

    ~Configuration();

    virtual void toJson() = 0;

    std::string _configurationPath;

    nlohmann::json _configuration;
};

} // namespace configuration