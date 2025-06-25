#pragma once

#include <engine/shape/Shape.hpp>

#include <engine/mesh/Mesh.hpp>

#include <memory>

using namespace engine::shape;

using namespace engine::mesh;

namespace component {

class Component {
  public:
    Component();

    virtual ~Component();

    virtual void create();

    virtual void load();

    virtual void update(float deltaTime);

    virtual void generateMesh();

    virtual std::vector<std::unique_ptr<Shape>> &getShapes();

    virtual glm::vec2 getPosition();

    void addShape(std::unique_ptr<Shape> shape);

    virtual void setX(float x);

    virtual void setY(float y);

  protected:
    std::vector<std::unique_ptr<Shape>> _shapes;

    glm::vec2 _position;
};

} // namespace component