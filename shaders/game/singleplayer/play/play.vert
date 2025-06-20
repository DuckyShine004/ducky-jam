#version 330 core

layout(location = 0) in vec3 iPosition;

uniform mat4 uModel;
uniform mat4 uProjection;

void main() {
    gl_Position = uProjection * uModel * vec4(iPosition, 1.0);
}
