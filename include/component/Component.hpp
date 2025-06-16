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

    virtual void create() = 0;

    virtual void load();

    virtual void generateMesh();

    virtual std::vector<std::unique_ptr<Shape>> &getShapes();

    void addShape(std::unique_ptr<Shape> shape);

  protected:
    std::vector<std::unique_ptr<Shape>> _shapes;
};

} // namespace component