#version 330 core

in vec2 f_uv;

out vec4 o_colour;

uniform sampler2D u_texture;
uniform float u_filter_radius;

void main() {
    vec2 offset = vec2(u_filter_radius) / vec2(textureSize(u_texture, 0));

    vec3 a = texture(u_texture, f_uv + vec2(-offset.x, offset.y)).rgb;
    vec3 b = texture(u_texture, f_uv + vec2(0.0f, offset.y)).rgb;
    vec3 c = texture(u_texture, f_uv + vec2(offset.x, offset.y)).rgb;

    vec3 d = texture(u_texture, f_uv + vec2(-offset.x, 0.0f)).rgb;
    vec3 e = texture(u_texture, f_uv).rgb;
    vec3 f = texture(u_texture, f_uv + vec2(offset.x, 0.0f)).rgb;

    vec3 g = texture(u_texture, f_uv + vec2(-offset.x, -offset.y)).rgb;
    vec3 h = texture(u_texture, f_uv + vec2(0.0f, -offset.y)).rgb;
    vec3 i = texture(u_texture, f_uv + vec2(offset.x, -offset.y)).rgb;

    vec3 result = e * 4.0f;

    result += (b + d + f + h) * 2.0f;
    result += a + c + g + i;
    result *= 1.0f / 16.0f;

    o_colour = vec4(result, 1.0f);
}
