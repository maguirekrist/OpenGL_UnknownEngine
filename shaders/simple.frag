#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D aTexture;
uniform sampler2D atlas;

const int tileSize = 16;

void main()
{
    vec2 mapSize = textureSize(aTexture, 0);
    //Tile here represents a 1 tile in the aTexture tile map, x, y is tile position, z, w is offset into atlas
    vec4 tile = texelFetch(aTexture, ivec2(gl_FragCoord) /  16, 0);

    vec2 normPixel = ivec2(gl_FragCoord) % 16;


    vec2 tileCoord = vec2( (((tile.z * 255) * tileSize) + normPixel.x),
                           (((tile.w * 255) * tileSize) + normPixel.y));

    vec4 inAtlas = texelFetch(atlas, ivec2(tileCoord), 0);

    color = inAtlas;
}