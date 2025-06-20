#include <external/glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include <engine/shader/Shader.hpp>

#include <utility/file/FileUtility.hpp>

using namespace utility::file;

namespace engine::shader {

Shader::Shader() = default;

Shader::Shader(const std::string &name) : _name(name) {
    this->_name = name;
}

void Shader::initialise() {
    this->createShaders();

    this->compileShaders();

    this->attachShaders();

    this->linkProgram();

    this->deleteShaders();
}

void Shader::use() {
    glUseProgram(this->_program);
}

void Shader::detach() {
    glUseProgram(0);
}

void Shader::createShaders() {
    std::string vertexShaderSource = FileUtility::getFileToString(this->_name + ".vert");
    std::string fragmentShaderSource = FileUtility::getFileToString(this->_name + ".frag");

    const char *vertexShaderCode = vertexShaderSource.c_str();
    const char *fragmentShaderCode = fragmentShaderSource.c_str();

    this->_vertexShader = glCreateShader(GL_VERTEX_SHADER);
    this->_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    glShaderSource(this->_vertexShader, 1, &vertexShaderCode, nullptr);
    glShaderSource(this->_fragmentShader, 1, &fragmentShaderCode, nullptr);
}

void Shader::compileShaders() {
    glCompileShader(this->_vertexShader);

    this->checkCompilationStatus(this->_vertexShader);

    glCompileShader(this->_fragmentShader);

    this->checkCompilationStatus(this->_fragmentShader);
}

void Shader::attachShaders() {
    this->_program = glCreateProgram();

    glAttachShader(this->_program, this->_vertexShader);
    glAttachShader(this->_program, this->_fragmentShader);
}

void Shader::linkProgram() {
    glLinkProgram(this->_program);

    this->checkProgramLinkStatus();
}

void Shader::deleteShaders() {
    glDeleteShader(this->_vertexShader);
    glDeleteShader(this->_fragmentShader);
}

void Shader::checkCompilationStatus(GLuint shader) {
    GLint status;

    GLchar infoLog[512];

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

    if (status == GL_FALSE) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);

        std::cout << "Compile Error\n" << infoLog << std::endl;
    }
}

void Shader::checkProgramLinkStatus() {
    GLint status;

    GLchar infoLog[512];

    glGetProgramiv(this->_program, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        glGetProgramInfoLog(this->_program, 512, nullptr, infoLog);

        std::cout << "Link Error\n" << infoLog << std::endl;
    }
}

void Shader::setMatrix4fv(const GLchar *name, glm::mat4 matrix) {
    GLint location = glGetUniformLocation(this->_program, name);

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

} // namespace engine::shader