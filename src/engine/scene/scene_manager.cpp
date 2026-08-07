#include "engine/scene/scene_manager.hpp"

#include "core/exceptions/invalid_argument_exception.hpp"

namespace engine::scene {

namespace exceptions = core::exceptions;

SceneManager::SceneManager() : m_scene(nullptr) {
}

void SceneManager::add_scene(const std::string &name, std::unique_ptr<Scene> scene) {
    m_scenes.emplace(name, std::move(scene));
}

void SceneManager::load_scene(const std::string &name) {
    auto iterator = m_scenes.find(name);

    if (iterator == m_scenes.end()) {
        throw exceptions::InvalidArgumentException("Scene '{}' not found.", name);
    }

    m_scene = iterator->second.get();
}

Scene *SceneManager::scene() {
    return m_scene;
}

} // namespace engine::scene
