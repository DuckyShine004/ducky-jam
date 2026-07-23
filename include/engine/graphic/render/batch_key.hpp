#pragma once

namespace engine::graphic::render {

struct BatchKey {
    int effect_id;
    int texture_id; // WARN: should be careful since if texture is removed, but new textures are added, it can point to a new texture

    bool operator==(const BatchKey &other) const = default;
};

} // namespace engine::graphic::render
