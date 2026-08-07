#pragma once

#include "engine/graphics/shader/shader.hpp"

#include <filesystem>
#include <memory>
#include <unordered_set>

namespace engine::graphics::shader {

class ShaderManager {
  public:
    ShaderManager();

    void load_shaders();

    engine::graphics::shader::Shader &use_shader(int shader_id);
    engine::graphics::shader::Shader &use_shader(const std::string &name);

    int get_shader_id(const std::string &name) const;

    engine::graphics::shader::Shader &get_shader(const std::string &name);
    engine::graphics::shader::Shader &get_shader(int shader_id);

    engine::graphics::shader::Shader &get_active_shader() const;

    void add_shader(const std::filesystem::path &path);

  private:
    static inline constexpr const char *vertex_shader_extension = ".vert";
    static inline constexpr const char *fragment_shader_extension = ".frag";

    static inline const std::filesystem::path shader_directory = "resources/shaders/";

    int m_id;

    std::unordered_set<std::string> m_shader_extensions;

    std::vector<std::unique_ptr<engine::graphics::shader::Shader>> m_shaders;
    std::unordered_map<std::string, int> m_shader_references;

    engine::graphics::shader::Shader *m_shader;
};

}; // namespace engine::graphics::shader
