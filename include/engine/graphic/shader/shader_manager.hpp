#pragma once

#include <memory>

#include "engine/graphic/shader/shader.hpp"

namespace engine::graphic::shader {

class ShaderManager {
  public:
    ShaderManager(const ShaderManager &) = delete;
    ShaderManager &operator=(const ShaderManager &) = delete;

    static ShaderManager &get_instance();

    void initialise();
    void use_shader(const std::string &name);
    engine::graphic::shader::Shader &get_shader(const std::string &name);
    engine::graphic::shader::Shader &get_shader(int shader_id);
    engine::graphic::shader::Shader &get_active_shader();

  private:
    ShaderManager();
    ~ShaderManager();

    void add_shader(const std::string &path);

    static inline constexpr const char *m_VERTEX_SHADER_EXTENSION = ".vert";
    static inline constexpr const char *m_FRAGMENT_SHADER_EXTENSION = ".frag";
    static inline constexpr const char *m_INCLUDE_EXTENSION = ".glsl";

    int m_shader_id;

    std::vector<std::unique_ptr<engine::graphic::shader::Shader>> m_shaders;
    std::unordered_map<std::string, int> m_shader_references;

    engine::graphic::shader::Shader *m_shader;
};

}; // namespace engine::graphic::shader
