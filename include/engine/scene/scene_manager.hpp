#pragma once

#include "engine/scene/scene.hpp"

namespace engine::scene {

class SceneManager {
  public:
    SceneManager() = default;

    void add_scene(const std::string &name, std::unique_ptr<Scene> scene);

  private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;
};

} // namespace engine::scene
