#include <component/game/singleplayer/play/area/Area.hpp>

#include <iostream>

namespace component::game::singleplayer::play::area {

Area::Area() = default;

void Area::create() {
    for (int i = 0; i < 1; i++) {
        std::unique_ptr<Lane> lane = std::make_unique<Lane>();

        lane->create();

        this->_lanes.push_back(std::move(lane));
    }
}

void Area::load() {
    generateMesh();
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

std::vector<std::unique_ptr<Lane>> &Area::getLanes() {
    return this->_lanes;
}

} // namespace component::game::singleplayer::play::area