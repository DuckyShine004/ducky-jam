#pragma once

#include <external/glad/glad.h>

#include <string>

namespace engine {
namespace shader {

class Shader {
  public:
    Shader(const std::string &name);

    void initialise();

  private:
    std::string _name;

    GLuint _vertexShader;
    GLuint _fragmentShader;

    GLuint _program;

    void createShaders();
    void compileShaders();
    void attachShaders();
    void linkProgram();
    void deleteShaders();

    void checkCompilationStatus(GLuint shader);
    void checkProgramLinkStatus();
};

} // namespace shader
} // namespace engine