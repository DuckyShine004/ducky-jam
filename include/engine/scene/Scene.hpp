#pragma once

namespace engine {
namespace scene {

class Scene {
    Scene();

    void update(float deltaTime);
    void render() const;

  private:
};

} // namespace scene
} // namespace engine
