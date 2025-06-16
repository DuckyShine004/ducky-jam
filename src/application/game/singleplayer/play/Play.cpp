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

    create();

    load();
}

void Play::create() {
    this->_area.create();
}

void Play::load() {
    this->_area.load();
}

void Play::update(float deltaTime) {
}

void Play::render() {
    Shader &shader = this->_shaders[0];

    shader.use();

    this->renderNotes();
}

void Play::renderNotes() {
}

} // namespace application::game::singleplayer::play