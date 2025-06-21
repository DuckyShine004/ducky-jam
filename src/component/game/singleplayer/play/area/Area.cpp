#include <component/game/singleplayer/play/area/Area.hpp>

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

namespace component::game::singleplayer::play::area {

Area::Area() : _noteModel(glm::mat4(1.0f)) {
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

    // Get the correct height offset based on the skin height, fps, scroll speed, bpm, and start time
    // for (HitObject &hitObject : hitObjects) {
    float scrollSpeed = 15.0f;

    float fps = 155.0f;

    float pxPerMs = fps * scrollSpeed * 0.001f;

    float width = 128.0f;

    // Suppose fps = 60hz, then scrollSpeed*fps=px/s or 1px/(1/60)ms
    // y = 1*60, 60px/second

    for (HitObject &hitObject : hitObjects) {
        int lane = hitObject.getLane();

        int startTime = hitObject.getStartTime();

        float x = lane * width;
        float y = pxPerMs * startTime;

        std::unique_ptr<Note> note = std::make_unique<Note>(x, y, 128.0f, 48.0f);

        this->_lanes[lane]->addNote(std::move(note));
    }

    generateMesh();
}

void Area::update(float deltaTime) {
    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        lane->update(deltaTime);
    }

    this->_noteModel = glm::translate(this->_noteModel, glm::vec3(0.0f, -15.0f, 0.0f));
}

void Area::generateMesh() {
    generateNoteMesh();
}

void Area::generateNoteMesh() {
    this->_noteMesh.initialise(GL_TRIANGLES, GL_DYNAMIC_DRAW);

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    size_t totalVertexCount = 0;
    size_t totalIndexCount = 0;

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            std::vector<std::unique_ptr<Shape>> &shapes = note->getShapes();

            totalVertexCount += shapes[0]->getVertices().size();
            totalIndexCount += shapes[0]->getIndices().size();
        }
    }

    vertices.reserve(totalVertexCount);
    indices.reserve(totalIndexCount);

    size_t offset = 0;

    for (std::unique_ptr<Lane> &lane : this->_lanes) {
        std::vector<std::unique_ptr<Note>> &notes = lane->getNotes();

        for (std::unique_ptr<Note> &note : notes) {
            std::vector<std::unique_ptr<Shape>> &shapes = note->getShapes();

            const std::vector<float> &noteVertices = shapes[0]->getVertices();
            const std::vector<unsigned int> &noteIndices = shapes[0]->getIndices();

            vertices.insert(vertices.end(), noteVertices.begin(), noteVertices.end());

            for (unsigned int index : noteIndices) {
                indices.push_back(index + offset);
            }

            offset += noteVertices.size() / 3;
        }
    }

    this->_noteMesh.setVertices(vertices);
    this->_noteMesh.setIndices(indices);
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