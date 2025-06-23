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

    // Get the correct height offset based on the skin height, fps, scroll speed, bpm, and start time
    // for (HitObject &hitObject : hitObjects) {
    float scrollSpeed = 20.0f;

    float fps = 155.0f;

    float pxPerMs = fps * scrollSpeed * 0.001f;

    float width = 128.0f;

    // Suppose fps = 60hz, then scrollSpeed*fps=px/s or 1px/(1/60)ms
    // y = 1*60, 60px/second
    float offset = pxPerMs * fps;

    for (HitObject &hitObject : hitObjects) {
        int lane = hitObject.getLane();

        int startTime = hitObject.getStartTime();
        int endTime = hitObject.getEndTime();

        float x = lane * width;
        float y = pxPerMs * startTime;

        float height = (endTime == 0) ? 48.0f : (endTime - startTime) * pxPerMs;

        std::unique_ptr<Note> note = std::make_unique<Note>(x, y, 128.0f, height);

        this->_lanes[lane]->addNote(std::move(note));

        this->_notes++;
    }

    generateMesh();
}

void Area::update(float deltaTime) {
    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        lane->update(deltaTime);
    }

    this->_noteModel = glm::translate(this->_noteModel, glm::vec3(0.0f, -20.0f, 0.0f));
}

void Area::generateMesh() {
    generateNoteMesh();
}

void Area::generateNoteMesh() {
    this->_noteMesh.initialise(GL_TRIANGLES, GL_DYNAMIC_DRAW, this->_notes);

    std::vector<Instance> instances;

    std::vector<float> quadVerts = {
        -0.5f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.5f, 0.5f, 0.0f,
    };
    std::vector<unsigned int> quadIdx = {
        0, 1, 2, 2, 3, 0,
    };
    this->_noteMesh.setVertices(quadVerts);
    this->_noteMesh.setIndices(quadIdx);

    instances.reserve(this->_notes);

    size_t offset = 0;

    int laneIndex = 0;

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            std::vector<std::unique_ptr<Shape>> &shapes = note->getShapes();

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