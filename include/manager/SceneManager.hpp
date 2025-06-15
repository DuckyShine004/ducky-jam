#pragma once

#include <engine/scene/Scene.hpp>

#include <memory>

using namespace engine::scene;

namespace manager {

class SceneManager {
  public:
    SceneManager(const SceneManager &) = delete;

    SceneManager &operator=(const SceneManager &) = delete;

    static SceneManager &getInstance();

    Scene &getScene();

    void setScene(std::unique_ptr<Scene> scene);

  private:
    SceneManager();

    ~SceneManager();

    std::unique_ptr<Scene> _scene;
};

} // namespace manager