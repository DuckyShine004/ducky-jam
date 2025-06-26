#include <component/game/singleplayer/play/area/Area.hpp>

#include "configuration/sound/SoundConfiguration.hpp"

#include "configuration/display/DisplayConfiguration.hpp"

#include <iostream>

using namespace configuration::sound;

using namespace configuration::display;

namespace component::game::singleplayer::play::area {

Area::Area() : _notes(0) {
}

void Area::create() {
    for (int i = 0; i < 7; i++) {
        std::unique_ptr<Lane> lane = std::make_unique<Lane>();

        this->_lanes.push_back(std::move(lane));
    }
}

void Area::load(const std::string &beatmapPath) {
    this->_beatmapParser.parse(beatmapPath);

    std::vector<HitObject> hitObjects = this->_beatmapParser.getHitObjects();

    std::vector<TimingPoint> timingPoints = this->_beatmapParser.getTimingPoints();

    float width = 128.0f;

    for (HitObject &hitObject : hitObjects) {
        int lane = hitObject.getLane();

        int startTime = hitObject.getStartTime();
        int endTime = hitObject.getEndTime();

        float x = lane * width;

        std::unique_ptr<Note> note = std::make_unique<Note>(x, width, startTime, endTime);

        this->_lanes[lane]->addNote(std::move(note));

        this->_notes++;
    }
    this->_noteMesh.initialise(GL_TRIANGLES, GL_DYNAMIC_DRAW, this->_notes);
    std::vector<float> quadVerts = {
        -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
    };
    std::vector<unsigned int> quadIdx = {
        0, 1, 2, 2, 3, 0,
    };
    this->_noteMesh.setVertices(quadVerts);
    this->_noteMesh.setIndices(quadIdx);
}

void Area::update(float deltaTime) {
    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        lane->update(deltaTime);
    }
}

void Area::generateNoteMesh(SoundSource &source) {
    std::vector<Instance> instances;

    instances.reserve(this->_notes);

    int laneIndex = 0;

    float position = source.getPosition();

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            float y;
            float height;

            this->calculateNotePosition(note, position, y, height);

            if (!this->isNoteInBound(y, height)) {
                continue;
            }

            note->setY(y);
            note->setHeight(height);

            glm::vec3 noteColour = this->getNoteColour(laneIndex);

            instances.push_back({note->getPosition(), note->getSize(), noteColour});
        }

        ++laneIndex;
    }

    this->_noteMesh.setInstances(instances);
}

Mesh &Area::getNoteMesh() {
    return this->_noteMesh;
}

std::vector<std::unique_ptr<Lane>> &Area::getLanes() {
    return this->_lanes;
}

void Area::calculateNotePosition(std::unique_ptr<Note> &note, float position, float &y, float &height) {
    SoundConfiguration &soundConfiguration = SoundConfiguration::getInstance();

    float offset = soundConfiguration.getOffset();
    float scrollSpeed = soundConfiguration.getScrollSpeed();

    float pixelsPerMs = scrollSpeed;

    float startTime = (float)note->getStartTime() - position + offset;
    float endTime = (note->getEndTime() == 0) ? 0.0f : (float)note->getEndTime() - position + offset;

    y = pixelsPerMs * startTime;

    height = (endTime == 0) ? 48.0f : (endTime - startTime) * pixelsPerMs;
}

bool Area::isNoteInBound(float y, float height) {
    DisplayConfiguration &displayConfiguration = DisplayConfiguration::getInstance();

    if (y + height <= 0 || y > displayConfiguration.getHeight()) {
        return false;
    }

    return true;
}

glm::vec3 Area::getNoteColour(int laneIndex) {
    switch (laneIndex) {
    case 0:
    case 2:
    case 4:
    case 6:
        return {1.0f, 1.0f, 1.0f};
    case 1:
    case 5:
        return {0.208f, 0.784f, 1.0f};
    }

    return {0.996f, 0.827f, 0.212f};
}

} // namespace component::game::singleplayer::play::area