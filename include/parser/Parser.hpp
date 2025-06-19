#pragma once

#include <nlohmann/json.hpp>

#include <string>

namespace parser {

class Parser {
  public:
    Parser();

    virtual ~Parser();

    virtual void parse(const std::string &path) = 0;

    nlohmann::json getParsedObject();

  private:
    nlohmann::json _parsedObject;
};

} // namespace parser