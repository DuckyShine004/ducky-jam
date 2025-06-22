#version 330 core

layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iColour;

uniform mat4 uModel;
uniform mat4 uProjection;

out vec3 fColour;

void main() {
    fColour = iColour;

    gl_Position = uProjection * uModel * vec4(iPosition, 1.0);
}
