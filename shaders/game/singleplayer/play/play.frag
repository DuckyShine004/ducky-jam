#version 330 core

in vec3 fColour;

out vec4 oFragmentColour;

void main() {
    oFragmentColour = vec4(fColour, 1.0f);
}
