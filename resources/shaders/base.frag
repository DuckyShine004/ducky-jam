#version 330 core

in vec2 f_uv;
in vec4 f_colour;

layout(location = 0) out vec4 o_scene;
layout(location = 1) out vec4 o_bloom;

uniform sampler2D u_texture;

uniform float u_bloom_intensity;

void main() {
    vec4 colour = texture(u_texture, f_uv) * f_colour;

    o_scene = colour;
    o_bloom = vec4(colour.rgb * u_bloom_intensity, colour.a);
}
