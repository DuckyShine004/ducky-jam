#version 330 core

in vec2 f_uv;
in vec4 f_colour;

out vec4 o_colour;

uniform vec2 u_shadow_size;

uniform float u_blur_radius;
uniform float u_corner_radius;

/* NOTE: SDF: Distance from centre of quad to corner */
float rounded_box_distance(vec2 position, vec2 half_size, float corner_radius) {
    vec2 distance_to_edge = abs(position) - half_size + vec2(corner_radius);

    return length(max(distance_to_edge, vec2(0.0f))) + min(max(distance_to_edge.x, distance_to_edge.y), 0.0f) - corner_radius;
}

void main() {
    float blur_radius = max(u_blur_radius, 0.0f);
    vec2 quad_size = u_shadow_size + vec2(blur_radius * 6.0f);

    vec2 local_position = (f_uv - vec2(0.5f)) * quad_size;
    vec2 half_size = max(u_shadow_size * 0.5f, vec2(0.0f));

    float corner_radius = clamp(u_corner_radius, 0.0f, min(half_size.x, half_size.y));

    float signed_distance = rounded_box_distance(local_position, half_size, corner_radius);

    float coverage;

    if (blur_radius <= 0.0001f) {
        coverage = signed_distance <= 0.0f ? 1.0f : 0.0f;
    } else {
        float normalised_distance = max(signed_distance, 0.0f) / blur_radius;

        coverage = exp(-0.5f * normalised_distance * normalised_distance);
    }

    o_colour = vec4(f_colour.rgb, f_colour.a * coverage);
}
