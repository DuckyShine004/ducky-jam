#include <engine/scene/Scene.hpp>

#include <application/game/singleplayer/play/Play.hpp>

#include <iostream>

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
    this->_area.update(deltaTime);
}

void Play::render() {
    this->renderNotes();
}

void Play::renderNotes() {
    Shader &shader = this->_shaders[0];

    shader.use();

    shader.setMatrix4fv("model", this->_area.getNoteModel());

    Mesh &noteMesh = this->_area.getNoteMesh();

    glBindVertexArray(noteMesh.getVao());

    glDrawElements(noteMesh.getPrimitive(), noteMesh.getIndexCount(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

} // namespace application::game::singleplayer::play