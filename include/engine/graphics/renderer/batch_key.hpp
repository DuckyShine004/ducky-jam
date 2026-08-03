#pragma once

#include "engine/graphics/effect/effect.hpp"

namespace engine::graphics::renderer {

struct BatchKey {
    engine::graphics::effect::EffectPtr effect;
    int texture_id; // WARN: should be careful since if texture is removed, but new textures are added, it can point to a new texture

    bool operator==(const BatchKey &other) const = default;
};

} // namespace engine::graphics::renderer
