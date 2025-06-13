#pragma once

#include <string>

namespace engine {
namespace shader {

class Shader {
  public:
    Shader(const std::string &name);

    void load();

  private:
    std::string _name;
};

} // namespace shader
} // namespace engine