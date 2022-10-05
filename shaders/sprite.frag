#version 330 core
out vec4 color;

in vec2 texCoords;

uniform sampler2D aTexture;



void main() {
    color = texture(aTexture, texCoords);
}