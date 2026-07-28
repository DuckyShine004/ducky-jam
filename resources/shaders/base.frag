#version 330 core

in vec2 f_uv;
in vec4 f_colour;

out vec4 o_colour;

uniform sampler2D u_texture;

void main() {
    o_colour = texture(u_texture, f_uv) * f_colour;
}
