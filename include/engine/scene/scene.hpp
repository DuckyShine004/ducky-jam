#pragma once

#include "engine/audio/audio_buffer.hpp"

#include "engine/ui/ui_node.hpp"

#include "engine/graphics/renderer/renderer.hpp"

namespace engine::scene {

class Scene {
  public:
    virtual ~Scene() = default;

    virtual void update(double delta_time) = 0;
    virtual void update_by_audio(engine::audio::AudioBuffer &audio_buffer, double track_time) = 0;

    void submit(engine::graphics::renderer::Renderer &renderer);

  protected:
    explicit Scene(std::unique_ptr<engine::ui::UiNode> root) : m_root(std::move(root)) {
    }

    std::unique_ptr<engine::ui::UiNode> m_root;
};

} // namespace engine::scene
