#pragma once

#include <external/glad/glad.h>

#include "engine/mesh/Instance.hpp"

#include <vector>

namespace engine::mesh {

class Mesh {
  public:
    Mesh();

    void initialise(GLenum primitive, GLenum usage, int notes);

    void setVertices(std::vector<float> vertices);

    void setIndices(std::vector<unsigned int> indices);

    void setInstances(std::vector<Instance> instances);

    void setPrimitive(GLenum primitive);

    void setUsage(GLenum usage);

    std::vector<float> &getVertices();

    std::vector<unsigned int> &getIndices();

    std::vector<Instance> &getInstances();

    GLenum getPrimitive();

    GLenum getUsage();

    GLuint getVao();

    GLuint getInstanceVbo();

    std::size_t getVertexCount();

    std::size_t getIndexCount();

    std::size_t getInstanceCount();

  private:
    std::vector<float> _vertices;

    std::vector<unsigned int> _indices;

    std::vector<Instance> _instances;

    std::size_t _vertexCount;
    std::size_t _indexCount;
    std::size_t _instanceCount;

    GLenum _primitive;

    GLenum _usage;

    GLuint _vao;
    GLuint _vbo;
    GLuint _ebo;
    GLuint _instanceVbo;

    bool _isInitialised;
};

} // namespace engine::mesh