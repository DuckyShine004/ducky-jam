#version 330 core

layout(location = 0) in vec2 v_position;
layout(location = 1) in vec2 v_uv;

out vec2 f_uv;

uniform mat4 u_model;
uniform mat4 u_projection;

void main() {
    vec4 world_space = u_model * vec4(v_position, 0.0f, 1.0f);

    f_uv = v_uv;
    gl_Position = u_projection * world_space;
}
