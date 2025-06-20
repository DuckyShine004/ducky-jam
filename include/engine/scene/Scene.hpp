#pragma once

#include <engine/shader/Shader.hpp>

#include <engine/shape/Shape.hpp>

#include <vector>

using namespace engine::shader;

using namespace engine::shape;

namespace engine::scene {

class Scene {
  public:
    Scene();

    virtual ~Scene();

    virtual void initialise() = 0;

    virtual void update(float deltaTime) = 0;

    virtual void render() = 0;

    virtual void load();

    virtual void updateProjectionMatrix(int width, int height);

  protected:
    std::vector<Shader> _shaders;

    std::vector<Shape> _shapes;

    Shader _shader;

    glm::mat4 _projectionMatrix;
};

} // namespace engine::scene
