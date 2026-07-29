#pragma once

#include "external/glad/glad.h"

namespace engine::graphic::blending::enums {

enum class BlendMode : GLenum {
    Zero = GL_ZERO,
    One = GL_ONE,
    SourceAlpha = GL_SRC_ALPHA,
    OneMinusSourceAlpha = GL_ONE_MINUS_SRC_ALPHA,
    DestinationAlpha = GL_DST_ALPHA,
    OneMinusDestinationAlpha = GL_ONE_MINUS_DST_ALPHA,
};

} // namespace engine::graphic::blending::enums
