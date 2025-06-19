#include <parser/Parser.hpp>

namespace parser {

Parser::Parser() = default;

Parser::~Parser() = default;

nlohmann::json Parser::getParsedObject() {
    return this->_parsedObject;
}

} // namespace parser