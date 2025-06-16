#pragma once

#include <external/glad/glad.h>

#include <glm/glm.hpp>

#include <string>

namespace engine::shader {

class Shader {
  public:
    Shader(const std::string &name);

    void initialise();

    void use();
    void detach();

    void setMatrix4fv(const GLchar *name, glm::mat4 matrix);

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

} // namespace engine::shader