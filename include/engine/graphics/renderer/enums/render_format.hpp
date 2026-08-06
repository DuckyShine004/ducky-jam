#pragma once

#include "external/glad/glad.h"

namespace engine::graphics::renderer::enums {

enum class FormatType : GLenum {
    GaussianBlur = GL_RGBA16F,
    MipChainBlur = GL_R11F_G11F_B10F,
};

} // namespace engine::graphics::renderer::enums
