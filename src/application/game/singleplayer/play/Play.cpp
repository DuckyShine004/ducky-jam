#include <engine/scene/Scene.hpp>

#include <application/game/singleplayer/play/Play.hpp>

// remember to create asset pool to load all shaders first
namespace application::game::singleplayer::play {

Play::Play() : Scene() {
    initialise();
}

void Play::initialise() {
    for (const char *shaderName : this->_SHADER_NAMES) {
        Shader shader(shaderName);

        shader.initialise();

        this->_shaders.push_back(shader);
    }
}

void Play::create() {
    this->_area.create();
}

void Play::update(float deltaTime) {
}

void Play::render() {
    for (Shader &shader : this->_shaders) {
        shader.use();
    }
}

} // namespace application::game::singleplayer::play