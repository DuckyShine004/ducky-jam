
#pragma once

#include "engine/graphics/model/enums/topology_type.hpp"
#include "engine/graphics/model/vertex.hpp"

#include "external/glad/glad.h"

namespace engine::graphics::model {

class Mesh {
  public:
    Mesh();

    void upload();
    void upload(const std::vector<engine::graphics::model::Vertex> &vertices, const std::vector<GLuint> &indices);
    void render(const engine::graphics::model::enums::TopologyType &topology);

    void add_vertex(engine::graphics::model::Vertex &vertex);
    void add_vertex(float x, float y, float u, float v, const core::structs::Vector4<std::uint8_t> &colour);

    void add_index(GLuint index);

    template <std::size_t N> void add_indices(const GLuint (&indices)[N]) {
        m_indices.insert(m_indices.end(), std::begin(indices), std::end(indices));
    }

    std::vector<engine::graphics::model::Vertex> &get_vertices();
    std::vector<GLuint> &get_indices();
    void clear_vertices();
    void clear();

  private:
    static inline constexpr unsigned int position_attribute = 0;
    static inline constexpr unsigned int uv_attribute = 1;
    static inline constexpr unsigned int colour_attribute = 2;

    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ibo;

    std::vector<engine::graphics::model::Vertex> m_vertices;
    std::vector<GLuint> m_indices;
    std::size_t m_indices_length;

    void draw_lines();
    void draw_triangles();
};

} // namespace engine::graphics::model
