#include <engine/scene/Scene.hpp>

#include <application/game/singleplayer/play/Play.hpp>

#include <engine/sound/SoundPlayer.hpp>
#include <engine/sound/SoundBuffer.hpp>

#include <iostream>

using namespace engine::sound;

namespace application::game::singleplayer::play {

Play::Play() : Scene() {
    initialise();
}

void Play::initialise() {
    ALuint soundId = SoundBuffer::getInstance().addSound("data/beatmaps/1831596/3759718/bgm.mp3");

    this->_source.play(soundId);

    for (const char *shaderName : this->_SHADER_NAMES) {
        Shader shader(shaderName);

        shader.initialise();

        this->_shaders.push_back(shader);
    }

    this->create();

    this->load("data/beatmaps/1831596/3759718/beatmap.osu");
}

void Play::create() {
    this->_area.create();
}

void Play::load(const std::string &beatmapPath) {
    this->_area.load(beatmapPath);
}

void Play::update(float deltaTime) {
    this->_area.update(deltaTime);
}

void Play::render() {
    this->renderNotes();
}

void Play::renderNotes() {
    Shader &shader = this->_shaders[0];

    this->_shader = shader;

    shader.use();

    shader.setMatrix4fv("uModel", this->_area.getNoteModel());
    shader.setMatrix4fv("uProjection", this->_projectionMatrix);

    Mesh &noteMesh = this->_area.getNoteMesh();

    glBindVertexArray(noteMesh.getVao());

    glDrawElements(noteMesh.getPrimitive(), noteMesh.getIndexCount(), GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

} // namespace application::game::singleplayer::play