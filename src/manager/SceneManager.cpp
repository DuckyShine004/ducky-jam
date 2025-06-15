#include <manager/SceneManager.hpp>

namespace manager {

SceneManager &SceneManager::getInstance() {
    static SceneManager instance;

    return instance;
}

SceneManager::SceneManager() = default;

SceneManager::~SceneManager() = default;

void SceneManager::setScene(std::unique_ptr<Scene> scene) {
    this->_scene = std::move(scene);
}

Scene &SceneManager::getScene() {
    return *this->_scene;
}

} // namespace manager