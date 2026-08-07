#pragma once

#include "engine/scene/scene.hpp"

namespace engine::scene {

class SceneManager {
  public:
    SceneManager();

    void add_scene(const std::string &name, std::unique_ptr<Scene> scene);

    /**
     * @brief Loads a valid scene for the given name.
     *
     * @param The name of the scene to load, e.g., load_scene("menu").
     *
     * @throws std::invalid_argument if scene name is invalid.
     */
    void load_scene(const std::string &name);

    Scene *scene();

  private:
    std::unordered_map<std::string, std::unique_ptr<Scene>> m_scenes;

    Scene *m_scene;
};

} // namespace engine::scene
