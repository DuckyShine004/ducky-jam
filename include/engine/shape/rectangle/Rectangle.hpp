#pragma once

#include <engine/shape/Shape.hpp>

#include <glm/glm.hpp>

namespace engine::shape::rectangle {

class Rectangle final : public Shape {
  public:
    Rectangle(glm::vec2 position);

    void translate(glm::vec2 offset) const override;

    void scale(glm::vec2 scale) const override;
    void scale(float scale) const override;

  private:
    // clang-format off
    static constexpr float _VERTICES[] = {
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
    };

    static constexpr unsigned int _INDICES[] = {
        0, 1, 2, 2, 0, 3,
    };
    // clang-format on
};

} // namespace engine::shape::rectangle