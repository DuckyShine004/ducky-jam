#include "engine/graphics/shader/shader_manager.hpp"

#include "core/exceptions/out_of_range_exception.hpp"
#include "core/exceptions/runtime_exception.hpp"
#include "core/logger/logger_macros.hpp"
#include "core/utility/file_utility.hpp"
#include "core/utility/string_utility.hpp"

#include <deque>
#include <unordered_set>

namespace engine::graphics::shader {

namespace utility = core::utility;
namespace exceptions = core::exceptions;

ShaderManager::ShaderManager() : m_id(0), m_shader(nullptr) {
    m_shader_extensions.emplace(vertex_shader_extension);
    m_shader_extensions.emplace(fragment_shader_extension);
}

void ShaderManager::load_shaders() {
    std::deque<std::filesystem::path> dq;

    dq.emplace_back(shader_directory);

    while (!dq.empty()) {
        int size = dq.size();

        for (int i = 0; i < size; ++i) {
            std::filesystem::path parent = dq.front();
            dq.pop_front();

            if (utility::FileUtility::is_file(parent)) {
                std::string extension = utility::FileUtility::extension(parent);

                if (m_shader_extensions.contains(extension)) {
                    add_shader(parent);
                }
            } else {
                const std::vector<std::filesystem::path> children = utility::FileUtility::children(parent);

                for (const std::filesystem::path &child : children) {
                    dq.emplace_back(child);
                }
            }
        }
    }
}

Shader &ShaderManager::use_shader(int shader_id) {
    m_shader = m_shaders[shader_id].get();
    m_shader->use();

    return *m_shader;
}

Shader &ShaderManager::use_shader(const std::string &name) {
    auto iterator = m_shader_references.find(name);

    if (iterator == m_shader_references.end()) {
        throw exceptions::OutOfRangeException("Shader '{}' was not found.", name);
    }

    int shader_id = iterator->second;

    m_shader = m_shaders[shader_id].get();
    m_shader->use();

    return *m_shader;
}

int ShaderManager::get_shader_id(const std::string &name) const {
    return m_shader_references.at(name);
}

Shader &ShaderManager::get_shader(const std::string &name) {
    auto iterator = m_shader_references.find(name);

    if (iterator == m_shader_references.end()) {
        throw exceptions::OutOfRangeException("Shader '{}' was not found.", name);
    }

    int shader_id = iterator->second;

    return *m_shaders[shader_id];
}

Shader &ShaderManager::get_shader(int shader_id) {
    if (shader_id < 0 || shader_id >= m_shaders.size()) {
        throw exceptions::OutOfRangeException("Invalid shader ID ({})", shader_id);
    }

    return *m_shaders[shader_id];
}

Shader &ShaderManager::get_active_shader() const {
    if (!m_shader) {
        throw exceptions::RuntimeException("No active shader is set. use_shader() must be called first");
    }

    return *m_shader;
}

void ShaderManager::add_shader(const std::filesystem::path &path) {
    const std::string extension = utility::FileUtility::extension(path);
    const std::string basename = utility::FileUtility::basename(path);

    const std::filesystem::path relative = path.lexically_relative(shader_directory);

    std::vector<std::string> split = utility::FileUtility::split(relative);

    if (!split.empty()) {
        split.pop_back();
        split.emplace_back(basename);
    }

    const std::string shader_name = utility::StringUtility::join(split, ".");

    LOG_INFO("Shader name: {}", shader_name);

    const std::filesystem::path shader_path = utility::FileUtility::parent(path) / basename;

    if (m_shader_references.find(shader_name) != m_shader_references.end()) {
        LOG_WARN("Shader '{}' is already loaded, skipping...", path.string());
        return;
    }

    std::filesystem::path vertex_shader_path = shader_path;
    vertex_shader_path += vertex_shader_extension;

    std::filesystem::path fragment_shader_path = shader_path;
    fragment_shader_path += fragment_shader_extension;

    m_shader_references.emplace(shader_name, m_id);
    m_shaders.emplace_back(std::make_unique<Shader>(vertex_shader_path, fragment_shader_path));

    ++m_id;
}

}; // namespace engine::graphics::shader
