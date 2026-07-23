#include "engine/graphic/shader/shader_manager.hpp"

#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"

using namespace engine::graphic::shader;

using namespace core::logger;
using namespace core::utility;

namespace engine::graphic::shader {

ShaderManager::ShaderManager() : m_shader(nullptr) {
}

ShaderManager::~ShaderManager() = default;

ShaderManager &ShaderManager::get_instance() {
    static ShaderManager instance;

    return instance;
}

void ShaderManager::initialise() {
    m_shader_id = 0;

    std::vector<std::string> paths = FileUtility::get_files_in_directory("resources/shaders/");

    for (const std::string &path : paths) {
        this->add_shader(path);
    }
}

void ShaderManager::use_shader(const std::string &name) {
    auto iterator = m_shader_references.find(name);

    if (iterator == m_shader_references.end()) {
        LOG_ERROR("Shader '{}' not found", name);
        std::terminate();
    }

    int shader_id = iterator->second;

    m_shader = m_shaders[shader_id].get();
    m_shader->use();
}

Shader &ShaderManager::get_shader(const std::string &name) {
    auto iterator = m_shader_references.find(name);

    if (iterator == m_shader_references.end()) {
        LOG_ERROR("Shader '{}' not found", name);
        std::terminate();
    }

    int shader_id = iterator->second;

    return *m_shaders[shader_id];
}

Shader &ShaderManager::get_shader(int shader_id) {
    if (shader_id < 0 || shader_id >= m_shaders.size()) {
        throw std::out_of_range("ERROR: Invalid shader ID");
    }

    return *m_shaders[shader_id];
}

Shader &ShaderManager::get_active_shader() {
    if (!m_shader) {
        LOG_ERROR("No active shader is set. use_shader() must be called first");
        std::terminate();
    }

    return *m_shader;
}

void ShaderManager::add_shader(const std::string &path) {
    std::string extension = FileUtility::get_extension_from_path(path);
    std::string basename = FileUtility::get_basename_from_path(path);

    if (extension == this->m_INCLUDE_EXTENSION) {
        LOG_INFO("Skipping include file '{}'", path);
        return;
    }

    std::string parent_directory = FileUtility::get_parent_directory(path);
    std::string shader_path = parent_directory + '/' + basename;

    if (m_shader_references.find(basename) != m_shader_references.end()) {
        LOG_WARN("Shader '{}' is already loaded, skipping...", path);
        return;
    }

    std::string vertex_shader_path = shader_path + m_VERTEX_SHADER_EXTENSION;
    std::string fragment_shader_path = shader_path + m_FRAGMENT_SHADER_EXTENSION;

    m_shader_references.emplace(basename, m_shader_id);
    m_shaders.emplace_back(std::make_unique<Shader>(vertex_shader_path, fragment_shader_path));

    ++m_shader_id;
}

}; // namespace engine::graphic::shader
