#pragma once

#include <engine/shape/Shape.hpp>

#include <glm/glm.hpp>

namespace engine::shape::rectangle {

class Rectangle final : public Shape {
  public:
    Rectangle(glm::vec2 position);

    void translate(glm::vec2 offset) override;

    void scale(glm::vec2 scale) override;
    void scale(float scale) override;

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

    void initialise();
};

} // namespace engine::shape::rectangle