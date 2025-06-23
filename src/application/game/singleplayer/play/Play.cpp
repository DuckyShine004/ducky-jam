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
    // ALuint soundId = SoundBuffer::getInstance().addSound("data/beatmaps/421541/948777/bgm.mp3");
    // ALuint soundId = SoundBuffer::getInstance().addSound("data/beatmaps/2325151/4983858/bgm.mp3");
    ALuint soundId = SoundBuffer::getInstance().addSound("data/beatmaps/2321277/4973089/bgm.mp3");
    // ALuint soundId = SoundBuffer::getInstance().addSound("data/beatmaps/974689/2220863/bgm.mp3");

    this->_source.play(soundId);

    for (const char *shaderName : this->_SHADER_NAMES) {
        Shader shader(shaderName);

        shader.initialise();

        this->_shaders.push_back(shader);
    }

    this->create();

    // this->load("data/beatmaps/421541/948777/beatmap.osu");
    // this->load("data/beatmaps/2325151/4983858/beatmap.osu");
    this->load("data/beatmaps/2321277/4973089/beatmap.osu");
    // this->load("data/beatmaps/974689/2220863/beatmap.osu");
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

    glDrawElementsInstanced(noteMesh.getPrimitive(), noteMesh.getIndexCount(), GL_UNSIGNED_INT, nullptr, noteMesh.getInstanceCount());

    glBindVertexArray(0);
}

} // namespace application::game::singleplayer::play