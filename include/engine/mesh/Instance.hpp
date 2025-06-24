#include <glm/glm.hpp>

namespace engine::mesh {

struct Instance {
    glm::vec2 offset;
    glm::vec2 size;
    glm::vec3 colour;
};

} // namespace engine::mesh
