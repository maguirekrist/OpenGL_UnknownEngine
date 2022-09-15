#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D aTexture;
uniform vec3 spriteColor;

void main() {
    color = vec4(spriteColor, 1.0) * texture(aTexture, TexCoord);
}