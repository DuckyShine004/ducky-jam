#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec2 iOffset;
layout(location = 2) in vec2 iSize;
layout(location = 3) in vec3 iColour;

uniform mat4 uModel;
uniform mat4 uProjection;

out vec3 fColour;

void main() {
    fColour = iColour;

    vec2 position = (iPosition + 0.5f).xy * iSize + iOffset;

    gl_Position = uProjection * vec4(position, 0.0, 1.0);
}
