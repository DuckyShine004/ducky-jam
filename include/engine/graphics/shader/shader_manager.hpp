#pragma once

#include "engine/graphics/shader/shader.hpp"

#include <memory>

namespace engine::graphics::shader {

class ShaderManager {
  public:
    ShaderManager();

    engine::graphics::shader::Shader &use_shader(int shader_id);
    engine::graphics::shader::Shader &use_shader(const std::string &name);
    int get_shader_id(const std::string &name) const;
    engine::graphics::shader::Shader &get_shader(const std::string &name);
    engine::graphics::shader::Shader &get_shader(int shader_id);
    engine::graphics::shader::Shader &get_active_shader() const;

  private:
    void add_shader(const std::string &path);

    static inline constexpr const char *m_VERTEX_SHADER_EXTENSION = ".vert";
    static inline constexpr const char *m_FRAGMENT_SHADER_EXTENSION = ".frag";
    static inline constexpr const char *m_INCLUDE_EXTENSION = ".glsl";

    int m_id;

    std::vector<std::unique_ptr<engine::graphics::shader::Shader>> m_shaders;

    std::unordered_map<std::string, int> m_shader_references;

    engine::graphics::shader::Shader *m_shader;
};

}; // namespace engine::graphics::shader
