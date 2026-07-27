#pragma once

#include "external/glad/glad.h"

#include "engine/graphic/model/vertex.hpp"
#include "engine/graphic/drawable/sprite.hpp"
#include "engine/graphic/render/batch_key.hpp"

namespace engine::graphic::render {

class Batch {
  public:
    Batch(engine::graphic::render::BatchKey &key);

    void add(const engine::graphic::drawable::Sprite &sprite);

    const engine::graphic::render::BatchKey &key() const;

    const std::vector<engine::graphic::model::Vertex> &vertices() const;
    const std::vector<GLuint> &indices() const;

  private:
    engine::graphic::render::BatchKey m_key;

    std::vector<engine::graphic::model::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
};

} // namespace engine::graphic::render
