#version 330 core
layout (location = 0) in vec4 vertex;

uniform mat4 view;

out vec2 texCoords;

void main() {
    gl_Position = vec4(vertex.xy, 0.0, 1.0);
    texCoords = vertex.zw;
}