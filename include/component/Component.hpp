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

    void addShape(std::unique_ptr<Shape> shape);

    std::vector<std::unique_ptr<Shape>> &getShapes();

  protected:
    std::vector<std::unique_ptr<Shape>> _shapes;
};

} // namespace component