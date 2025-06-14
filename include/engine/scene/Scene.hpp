#pragma once

namespace engine::scene {

class Scene {
    Scene();

    void update(float deltaTime);
    void render() const;

  private:
};

} // namespace engine::scene
