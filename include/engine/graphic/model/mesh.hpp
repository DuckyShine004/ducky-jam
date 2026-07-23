
#pragma once

#include "external/glad/glad.h"

#include "engine/graphic/model/vertex.hpp"
#include "engine/graphic/model/enums/topology_type.hpp"

namespace engine::graphic::model {

class Mesh {
  public:
    Mesh();

    void upload();
    void upload(const std::vector<engine::graphic::model::Vertex> &vertices, const std::vector<GLuint> &indices);
    void render(const engine::graphic::model::enums::TopologyType &topology);

    void add_vertex(engine::graphic::model::Vertex &vertex);
    void add_vertex(glm::vec2 &position);
    void add_vertex(float x, float y);
    void add_vertex(float x, float y, const glm::vec2 &uv);
    void add_vertex(float x, float y, float u, float v);

    void add_index(GLuint index);

    template <std::size_t N> void add_vertices(const float (&vertices)[N][3]) {
        for (int i = 0; i < N; ++i) {
            float x = vertices[i][0];
            float y = vertices[i][1];

            m_vertices.emplace_back(x, y);
        }
    }

    template <std::size_t N> void add_indices(const GLuint (&indices)[N]) {
        m_indices.insert(m_indices.end(), std::begin(indices), std::end(indices));
    }

    std::vector<engine::graphic::model::Vertex> &get_vertices();
    std::vector<GLuint> &get_indices();
    void clear_vertices();
    void clear();

  private:
    static inline constexpr unsigned int m_POSITION_ATTRIBUTE = 0;
    static inline constexpr unsigned int m_UV_ATTRIBUTE = 1;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;

    std::vector<engine::graphic::model::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::size_t m_indices_length;

    void draw_lines();
    void draw_triangles();
};

} // namespace engine::graphic::model
