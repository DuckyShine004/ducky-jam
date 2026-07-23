#pragma once

#include <vector>

#include "engine/graphic/model/mesh.hpp"
#include "engine/graphic/render/batch.hpp"

namespace engine::graphic::render {

class Renderer {
  public:
    Renderer();

    // sprite, batch key
    void queue(const engine::graphic::model::Sprite &sprite);
    void render();

  private:
    // single mesh to avoid uploading gpu data in each batch
    engine::graphic::model::Mesh m_mesh;

    // could maybe upload batches concurrently? But then downside is that draw ordering is messed up
    std::vector<engine::graphic::render::Batch> m_batches;
};

} // namespace engine::graphic::render
