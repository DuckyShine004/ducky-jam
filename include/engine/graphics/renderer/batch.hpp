#pragma once

#include "external/glad/glad.h"

#include "engine/graphics/model/quad.hpp"
#include "engine/graphics/model/vertex.hpp"

#include "engine/graphics/renderer/batch_key.hpp"

namespace engine::graphics::renderer {

class Batch {
  public:
    Batch(const engine::graphics::renderer::BatchKey &key);

    void add(const engine::graphics::model::Quad &quad);

    const engine::graphics::renderer::BatchKey &key() const;

    const std::vector<engine::graphics::model::Vertex> &vertices() const;
    const std::vector<GLuint> &indices() const;

  private:
    engine::graphics::renderer::BatchKey m_key;

    std::vector<engine::graphics::model::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
};

} // namespace engine::graphics::renderer
