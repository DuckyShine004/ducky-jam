#version 330 core

in vec2 f_uv;

out vec4 o_colour;

uniform sampler2D u_texture;

uniform bool u_horizontal;

const float WEIGHTS[5] = float[](
    0.227027,
    0.1945946,
    0.1216216,
    0.054054,
    0.016216
);

void main() {
    vec2 uv_offset = 1.0f / vec2(textureSize(u_texture, 0));
    vec3 result = texture(u_texture, f_uv).rgb * WEIGHTS[0];

    if (u_horizontal) {
        for (int i = 1; i < 5; ++i) {
            float offset = uv_offset.x * float(i);

            result += texture(u_texture, f_uv + vec2(offset, 0.0f)).rgb * WEIGHTS[i];
            result += texture(u_texture, f_uv - vec2(offset, 0.0f)).rgb * WEIGHTS[i];
        }
    } else {
        for (int i = 1; i < 5; ++i) {
            float offset = uv_offset.y * float(i);

            result += texture(u_texture, f_uv + vec2(0.0f, offset)).rgb * WEIGHTS[i];
            result += texture(u_texture, f_uv - vec2(0.0f, offset)).rgb * WEIGHTS[i];
        }
    }

    o_colour = vec4(result, 1.0);
}
