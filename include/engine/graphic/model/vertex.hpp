#pragma once

#include <glm/glm.hpp>

namespace engine::graphic::model {

struct Vertex {
    glm::vec2 position;
    glm::vec2 uv;

    Vertex() : Vertex(0.0f, 0.0f, 0.0f, 0.0f) {
    }

    Vertex(glm::vec2 &position) : Vertex(position.x, position.y, 0.0f, 0.0f) {
    }

    Vertex(float x, float y) : Vertex(x, y, 0.0f, 0.0f) {
    }

    Vertex(float x, float y, const glm::vec2 &uv) : Vertex(x, y, uv.x, uv.y) {
    }
    Vertex(float x, float y, float u, float v) : position(x, y), uv(u, v) {
    }
};

} // namespace engine::graphic::model
