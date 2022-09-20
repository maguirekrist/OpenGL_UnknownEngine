#version 330 core

out vec4 color;

uniform sampler2D aTexture;
uniform sampler2D atlas;

uniform sampler2D lightMap;


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
    //tileDiffuse
    //vec4 tileColor = texelFetch(lightMap, ivec2(worldPosition), 0);
    vec4 tileColor = texture(lightMap, vec2(worldPosition.x / mapSize.x, worldPosition.y / mapSize.y));
    //vec2 normPixel = ivec2(gl_FragCoord) % 16;

    vec2 inTilePosition = vec2(fract(worldPosition.x) * tileSize, fract(worldPosition.y) * tileSize);
    inTilePosition = vec2(inTilePosition.x / atlasSize.x, inTilePosition.y / atlasSize.y);

    float atlasOffsetX = tile.z * 255;
    float atlasOffsetY = tile.w * 255;

    vec2 tileCoord = vec2( ((atlasOffsetX * tileSize) / atlasSize.x),
                           ((atlasOffsetY * tileSize) / atlasSize.y));

    //Translate tileCoord by inTilePosition
    tileCoord = tileCoord + inTilePosition;
    //vec4 inAtlas = texelFetch(atlas, ivec2(tileCoord), 0);
    color = texture(atlas, tileCoord) * tileColor;
}