#version 330 core

in vec2 f_uv;

out vec4 o_colour;

uniform sampler2D u_scene;
uniform sampler2D u_bloom;

uniform float u_bloom_strength;

void main() {
    vec3 scene = texture(u_scene, f_uv).rgb;
    vec3 bloom = texture(u_bloom, f_uv).rgb;

    o_colour = vec4(scene + bloom * u_bloom_strength, 1.0f);
}
