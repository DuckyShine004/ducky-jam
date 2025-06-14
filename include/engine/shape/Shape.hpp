#pragma once

#include <glm/glm.hpp>

#include <vector>

namespace engine::shape {

class Shape {
  public:
    virtual ~Shape();

    virtual void translate(glm::vec2 offset) const = 0;

    virtual void scale(glm::vec2 scale) const = 0;
    virtual void scale(float scale) const = 0;

    std::vector<float> getVertices() const;
    std::vector<unsigned int> getIndices() const;

  protected:
    Shape() = default;

    glm::vec2 _position;

    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;
};

} // namespace engine::shape