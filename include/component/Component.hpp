#pragma once

#include <engine/shape/Shape.hpp>

#include <memory>

using namespace engine::shape;

namespace component {

class Component {
  public:
    Component();

    virtual ~Component();

    virtual void create() = 0;

    virtual void load() = 0;

    virtual void generateMesh() = 0;

    virtual std::vector<std::unique_ptr<Shape>> &getShapes();

    void addShape(std::unique_ptr<Shape> shape);

  protected:
    std::vector<std::unique_ptr<Shape>> _shapes;
};

} // namespace component