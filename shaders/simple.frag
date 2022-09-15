#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D aTexture;
uniform sampler2D atlas;

uniform mat4 view; //Matrix is responsible for converting screen coord (gl_FragCoord) to world coodinates.
                    //View will also translate and scale world (scroll/zoom)

const int tileSize = 16;

void main()
{
    vec2 mapSize = textureSize(aTexture, 0);
    vec2 atlasSize = textureSize(atlas, 0);
    //Tile here represents a 1 tile in the aTexture tile map, x, y is tile position, z, w is offset into atlas
    vec2 worldPosition = vec2(view * vec4(gl_FragCoord.xy, 0, 1));

    vec4 tile = texelFetch(aTexture, ivec2(worldPosition), 0);

    //Tile is correct
    //Needs:
    //Transform the


    //vec2 normPixel = ivec2(gl_FragCoord) % 16;

    vec2 inTilePosition = vec2(fract(worldPosition.x) * tileSize, fract(worldPosition.y) * tileSize);
    inTilePosition = vec2(inTilePosition.x / atlasSize.x, inTilePosition.y / atlasSize.y);

    float atlasOffsetX = tile.z * 255;
    float atlasOffsetY = tile.w * 255;

    vec2 tileCoord = vec2( (((tile.z * 255) * tileSize) / atlasSize.x),
                           (((tile.w * 255) * tileSize)) / atlasSize.y);

    //Translate tileCoord by inTilePosition
    tileCoord = tileCoord + inTilePosition;

    //vec4 inAtlas = texelFetch(atlas, ivec2(tileCoord), 0);
    color = texture(atlas, tileCoord);
}