#pragma once

#include "external/glad/glad.h"

#include "engine/graphics/blending/enums/blend_equation.hpp"
#include "engine/graphics/blending/enums/blend_mode.hpp"

namespace engine::graphics::blending {

struct BlendParameters {
    bool enabled = true;

    enums::BlendEquation equation = enums::BlendEquation::Add;
    enums::BlendMode source = enums::BlendMode::SourceAlpha;
    enums::BlendMode destination = enums::BlendMode::OneMinusSourceAlpha;

    void apply() const {
        if (!enabled) {
            glDisable(GL_BLEND);
            return;
        }

        glEnable(GL_BLEND);
        glBlendEquation(static_cast<GLenum>(equation));
        glBlendFunc(static_cast<GLenum>(source), static_cast<GLenum>(destination));
    }

    bool operator==(const BlendParameters &) const = default;
};

} // namespace engine::graphics::blending
