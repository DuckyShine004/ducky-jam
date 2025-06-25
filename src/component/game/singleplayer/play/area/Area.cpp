#include <component/game/singleplayer/play/area/Area.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace component::game::singleplayer::play::area {

Area::Area() : _noteModel(glm::mat4(1.0f)), _notes(0) {
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

    this->_noteModel = glm::translate(this->_noteModel, glm::vec3(0.0f, -20.0f, 0.0f));
}

void Area::generateNoteMesh(SoundSource &source) {

    std::vector<Instance> instances;

    instances.reserve(this->_notes);

    int laneIndex = 0;

    float position = source.getPosition();

    float scrollSpeed = 3000.0f;

    float pxPerMs = scrollSpeed * 0.001f;

    float offsetMs = 300.0f;

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            // Calculate the offset
            float startTime = (float)note->getStartTime() - position + offsetMs;
            float endTime = (note->getEndTime() == 0) ? 0.0f : (float)note->getEndTime() - position + offsetMs;

            // Calculate the actual y value
            float y = pxPerMs * startTime;
            float height = (endTime == 0) ? 48.0f : (endTime - startTime) * pxPerMs;
            float endY = y + height;

            // Calculate bounds
            if (y + height <= 0 || y > 1440) {
                continue;
            }

            note->setY(y);
            note->setHeight(height);

            glm::vec3 laneColour;

            switch (laneIndex) {
            case 0:
            case 2:
            case 4:
            case 6:
                laneColour = {1.0f, 1.0f, 1.0f}; // white
                break;
            case 1:
            case 5:
                laneColour = {0.208f, 0.784f, 1.0f}; // blue
                break;
            case 3:
                laneColour = {0.996f, 0.827f, 0.212f}; // yellow
                break;
            }

            instances.push_back({note->getPosition(), note->getSize(), laneColour});
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

glm::mat4 &Area::getNoteModel() {
    return this->_noteModel;
}

} // namespace component::game::singleplayer::play::area