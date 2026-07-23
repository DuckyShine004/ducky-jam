#pragma once

#include <glm/glm.hpp>

#include <string>

#include "external/glad/glad.h"

namespace engine::graphic::shader {

class Shader {
  public:
    Shader();
    Shader(const std::string &vertex_shader_path, const std::string &fragment_shader_path);

    void use();
    void detach();

    void set_float(const GLchar *name, float value);
    void set_integer(const GLchar *name, int value);

    void set_vector2f(const GLchar *name, float x, float y);
    void set_vector2f(const GLchar *name, glm::vec2 vector);

    void set_vector3f(const GLchar *name, float x, float y, float z);
    void set_vector3f(const GLchar *name, glm::vec3 vector);
    void set_vector3f(const GLchar *name, const float (&array)[3]);

    void set_matrix4fv(const GLchar *name, glm::mat4 matrix);

  private:
    std::string m_vertex_shader_path;
    std::string m_fragment_shader_path;

    GLuint m_vertex_shader;
    GLuint m_fragment_shader;

    GLuint m_program;

    void initialise();

    void create_shaders();
    void compile_shaders();
    void attach_shaders();
    void link_program();
    void delete_shaders();

    void check_compilation_status(GLuint shader);
    void check_program_link_status();
};

} // namespace engine::graphic::shader
