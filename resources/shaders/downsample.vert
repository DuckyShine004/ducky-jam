#version 330 core

out vec2 f_uv;

void main() {
    const vec2 positions[3] = vec2[](
            vec2(-1.0f, -1.0f),
            vec2(3.0f, -1.0f),
            vec2(-1.0f, 3.0f)
        );

    vec2 position = positions[gl_VertexID];

    f_uv = position * 0.5f + 0.5f;

    gl_Position = vec4(position, 0.0f, 1.0f);
}
