#pragma once

#include <vector>

#include "engine/graphic/model/mesh.hpp"
#include "engine/graphic/model/quad.hpp"

#include "engine/graphic/drawable/sprite.hpp"

#include "engine/graphic/render/batch.hpp"

namespace engine::graphic::render {

class Renderer {
  public:
    Renderer();

    void queue(const engine::graphic::model::Quad &quad);
    void queue(const engine::graphic::drawable::Sprite &sprite);

    void render();

  private:
    engine::graphic::model::Mesh m_mesh;

    std::vector<engine::graphic::render::Batch> m_batches;
};

} // namespace engine::graphic::render
