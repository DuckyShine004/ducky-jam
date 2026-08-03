#version 330 core

in vec2 f_uv;
in vec4 f_colour;

layout(location = 0) out vec4 o_scene;
layout(location = 1) out vec4 o_bloom;

/* NOTE: x = TL, y = TR, z = BR, w = BL */
uniform vec4 u_corner_radius;
uniform vec2 u_draw_size;
uniform vec2 u_shape_size;

uniform vec2 u_shadow_offset;
uniform float u_shadow_blur;
uniform vec4 u_shadow_colour;

uniform float u_bloom_intensity;

float corner_radius_at(vec2 position, vec4 radius) {
    if (position.x > 0.0f) {
        return position.y > 0.0f ? radius.y : radius.z;
    }

    return position.y > 0.0f ? radius.x : radius.w;
}

float rounded_box_distance(vec2 position, vec2 half_size, vec4 radius) {
    float selected_radius = clamp(corner_radius_at(position, radius), 0.0f, min(half_size.x, half_size.y));
    vec2 distance_to_edge = abs(position) - half_size + selected_radius;

    return length(max(distance_to_edge, vec2(0.0f))) + min(max(distance_to_edge.x, distance_to_edge.y), 0.0f) - selected_radius;
}

void main() {
    vec2 local_position = (f_uv - vec2(0.5f)) * u_draw_size;
    vec2 half_size = max(u_shape_size * 0.5f, vec2(0.0f));

    float fill_distance = rounded_box_distance(local_position, half_size, u_corner_radius);
    float fill_smoothing = max(fwidth(fill_distance), 0.0001f);
    float fill_coverage = 1.0f - smoothstep(-fill_smoothing, fill_smoothing, fill_distance);
    float fill_alpha = f_colour.a * fill_coverage;

    vec2 shadow_position = local_position - u_shadow_offset;
    float shadow_distance = rounded_box_distance(shadow_position, half_size, u_corner_radius);
    float shadow_coverage;

    if (u_shadow_blur <= 0.0001f) {
        float shadow_smoothing = max(fwidth(shadow_distance), 0.0001f);
        shadow_coverage = 1.0f - smoothstep(-shadow_smoothing, shadow_smoothing, shadow_distance);
    } else {
        float normalised_distance = max(shadow_distance, 0.0f) / u_shadow_blur;
        shadow_coverage = exp(-0.5f * normalised_distance * normalised_distance);
    }

    // The shadow is behind the fill, so retain only the portion not covered by it.
    float shadow_alpha = u_shadow_colour.a * shadow_coverage * (1.0f - fill_alpha);
    float alpha = fill_alpha + shadow_alpha;

    if (alpha <= 0.0001f) {
        discard;
    }

    vec3 premultiplied_colour = f_colour.rgb * fill_alpha + u_shadow_colour.rgb * shadow_alpha;
    vec3 colour = premultiplied_colour / alpha;

    o_scene = vec4(colour, alpha);

    // Bloom applies to the element itself, not its drop shadow.
    o_bloom = vec4(f_colour.rgb * u_bloom_intensity, fill_alpha);
}
