#pragma once

#include <external/glad/glad.h>

#include <vector>

namespace engine::mesh {

class Mesh {
  public:
    Mesh();

    void initialise(GLenum primitive, GLenum usage);

    void setColours(std::vector<float> colours);

    void setVertices(std::vector<float> vertices);

    void setIndices(std::vector<unsigned int> indices);

    void setPrimitive(GLenum primitive);

    void setUsage(GLenum usage);

    std::vector<float> &getColours();

    std::vector<float> &getVertices();

    std::vector<unsigned int> &getIndices();

    GLenum getPrimitive();

    GLenum getUsage();

    GLuint getVao();

    GLuint getCbo();

    std::size_t getVertexCount();

    std::size_t getIndexCount();

    std::size_t getColourCount();

  private:
    std::vector<float> _colours;
    std::vector<float> _vertices;

    std::vector<unsigned int> _indices;

    std::size_t _vertexCount;
    std::size_t _indexCount;
    std::size_t _colourCount;

    GLenum _primitive;

    GLenum _usage;

    GLuint _vao;
    GLuint _vbo;
    GLuint _cbo;
    GLuint _ebo;

    bool _isInitialised;
};

} // namespace engine::mesh