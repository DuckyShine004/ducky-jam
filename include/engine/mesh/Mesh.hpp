#pragma once

#include <external/glad/glad.h>

#include <vector>

namespace engine::mesh {

class Mesh {
  public:
    Mesh();

    void setVertices(std::vector<float> &vertices);
    void setIndices(std::vector<unsigned int> &indices);

    void setPrimitive(GLenum primitive);

    std::vector<float> &getVertices();
    std::vector<unsigned int> &getIndices();

    GLenum getPrimitive();

    std::size_t getVertexCount();
    std::size_t getIndexCount();

  private:
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;

    std::size_t _vertexCount;
    std::size_t _indexCount;

    GLenum _primitive;
};

} // namespace engine::mesh