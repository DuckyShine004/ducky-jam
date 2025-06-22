#version 330 core

in vec3 fColour;

out vec4 oFragmentColour;

void main() {
    vec3 g = vec3(0.0f, 1.0f, 0.0f);

    oFragmentColour = vec4(fColour, 1.0f);
}
