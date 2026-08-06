#include "engine/scene/scene_manager.hpp"

namespace engine::scene {

void SceneManager::add_scene(const std::string &name, std::unique_ptr<Scene> scene) {
    m_scenes.emplace(name, std::move(scene));
}

} // namespace engine::scene
