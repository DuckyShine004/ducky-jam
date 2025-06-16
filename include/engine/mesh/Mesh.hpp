#pragma once

#include <external/glad/glad.h>

#include <vector>

namespace engine::mesh {

class Mesh {
  public:
    Mesh();

    void initialise(GLenum primitive, GLenum usage);

    void setVertices(std::vector<float> vertices);
    void setIndices(std::vector<unsigned int> indices);

    void setPrimitive(GLenum primitive);

    void setUsage(GLenum usage);

    std::vector<float> &getVertices();
    std::vector<unsigned int> &getIndices();

    GLenum getPrimitive();

    GLenum getUsage();

    GLuint getVao();

    std::size_t getVertexCount();
    std::size_t getIndexCount();

  private:
    std::vector<float> _vertices;
    std::vector<unsigned int> _indices;

    std::size_t _vertexCount;
    std::size_t _indexCount;

    GLenum _primitive;

    GLenum _usage;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;

    bool _isInitialised;
};

} // namespace engine::mesh