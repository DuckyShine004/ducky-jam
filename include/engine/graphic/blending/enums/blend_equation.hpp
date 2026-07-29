#pragma once

#include "external/glad/glad.h"

namespace engine::graphic::blending::enums {

enum class BlendEquation : GLenum {
    Add = GL_FUNC_ADD,
    Subtract = GL_FUNC_SUBTRACT,
    ReverseSubtract = GL_FUNC_REVERSE_SUBTRACT,
    Minimum = GL_MIN,
    Maximum = GL_MAX,
};

} // namespace engine::graphic::blending::enums
