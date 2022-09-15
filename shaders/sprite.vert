#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec2 tileCoord;

const int tileSize = 16;
const int atlasWidth = 192;
const int atlasHeight = 176;

void main() {
    TexCoord = vec2(((tileCoord.x + vertex.z) * tileSize) / atlasWidth, ((tileCoord.y + vertex.w) * tileSize) / atlasHeight);
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}