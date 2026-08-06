#version 330 core

in vec2 f_uv;

out vec4 o_colour;

uniform sampler2D u_texture;

void main() {
    vec2 uv_offset = 1.0f / vec2(textureSize(u_texture, 0));

    float x = uv_offset.x;
    float y = uv_offset.y;

    vec3 a = texture(u_texture, vec2(f_uv.x - 2.0f * x, f_uv.y + 2.0f * y)).rgb;
    vec3 b = texture(u_texture, vec2(f_uv.x, f_uv.y + 2.0f * y)).rgb;
    vec3 c = texture(u_texture, vec2(f_uv.x + 2.0f * x, f_uv.y + 2.0f * y)).rgb;

    vec3 d = texture(u_texture, vec2(f_uv.x - 2.0f * x, f_uv.y)).rgb;
    vec3 e = texture(u_texture, vec2(f_uv.x, f_uv.y)).rgb;
    vec3 f = texture(u_texture, vec2(f_uv.x + 2.0f * x, f_uv.y)).rgb;

    vec3 g = texture(u_texture, vec2(f_uv.x - 2.0f * x, f_uv.y - 2.0f * y)).rgb;
    vec3 h = texture(u_texture, vec2(f_uv.x, f_uv.y - 2.0f * y)).rgb;
    vec3 i = texture(u_texture, vec2(f_uv.x + 2.0f * x, f_uv.y - 2.0f * y)).rgb;

    vec3 j = texture(u_texture, vec2(f_uv.x - x, f_uv.y + y)).rgb;
    vec3 k = texture(u_texture, vec2(f_uv.x + x, f_uv.y + y)).rgb;
    vec3 l = texture(u_texture, vec2(f_uv.x - x, f_uv.y - y)).rgb;
    vec3 m = texture(u_texture, vec2(f_uv.x + x, f_uv.y - y)).rgb;

    vec3 result = e * 0.125;

    result += (a + c + g + i) * 0.03125;
    result += (b + d + f + h) * 0.0625;
    result += (j + k + l + m) * 0.125;

    o_colour = vec4(result, 1.0f);
}
