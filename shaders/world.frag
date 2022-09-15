#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D atlasTexture;
uniform sampler2D tileMap;

const int tileSize = 16;
const int atlasWidth = 192;
const int atlasHeight = 176;

vec2 calculateTileCoord(vec2 pixel) {
    //Pixel is current in normalized device coordinates, our mapTexture's tiles are in world coordinates
    vec4 texel = texelFetch(tileMap, ivec2(pixel), 0);
    vec2 tileCoord = texel.zw;
    return vec2(((tileCoord.x + pixel.x) * tileSize) / atlasWidth, ((tileCoord.y + pixel.y) * tileSize) / atlasHeight);

    //gl_FragCoord
}


//TexCoord = vec2(((tileCoord.x + vertex.z) * tileSize) / atlasWidth, ((tileCoord.y + vertex.w) * tileSize) / atlasHeight);

void main() {
    ivec2 size = textureSize(tileMap, 0);
    int SIZE_U = size.x;
    int SIZE_V = size.y;

    float du = 1.0 / SIZE_U;
    float dv = 1.0 / SIZE_V;


    color = texture(tileMap, TexCoord);
}