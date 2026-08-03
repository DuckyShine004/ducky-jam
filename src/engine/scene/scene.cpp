#include "engine/scene/scene.hpp"

#include "engine/ui/constraint.hpp"

using namespace engine::graphics::renderer;

using namespace engine::ui;

namespace engine::scene {

void Scene::submit(Renderer &renderer) {
    Constraint constraint{
        .minimum = {0.0f, 0.0f},
        .maximum = {2560.0f, 1440.0f},
    };

    m_root->measure(constraint);

    m_root->arrange({
        .x = 0.0f,
        .y = 0.0f,
        .width = constraint.maximum.w,
        .height = constraint.maximum.h,
    });

    m_root->submit(renderer);
}

} // namespace engine::scene
