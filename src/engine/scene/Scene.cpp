#include <engine/scene/Scene.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace engine::scene {

Scene::Scene() : _projectionMatrix(glm::mat4(1.0f)) {};

Scene::~Scene() = default;

void Scene::create() {
}

void Scene::load() {
}

void Scene::updateProjectionMatrix(int width, int height) {
    this->_projectionMatrix = glm::ortho(0.0f, (float)width, 0.0f, (float)height, -1.0f, 1.0f);

    this->_shader.setMatrix4fv("uProjection", this->_projectionMatrix);
}

} // namespace engine::scene