#version 330 core

out vec4 color;

uniform sampler2D aTexture;
uniform sampler2DArray atlas; //because atlas is now a Texture array we need the proper sampler type for that

uniform sampler2D lightMap;
uniform sampler1D ambient; //1D gradient texture that is used for day-night changes


uniform mat4 view; //Matrix is responsible for converting screen coord (gl_FragCoord) to world coodinates.
                    //View will also translate and scale world (scroll/zoom)
uniform float worldTime; // This value is used to sample ambientGradient to color our world for day/night cycle

const int tileSize = 1024;

void main()
{
    vec2 mapSize = textureSize(aTexture, 0);
    vec3 atlasSize = textureSize(atlas, 0);
    //Tile here represents a 1 tile in the aTexture tile map, x, y is tile position, z, w is offset into atlas
    vec2 worldPosition = vec2(view * vec4(gl_FragCoord.xy, 0, 1));
    vec4 tile = texelFetch(aTexture, ivec2(worldPosition), 0);
    //tileDiffuse
    //vec4 tileColor = texelFetch(lightMap, ivec2(worldPosition), 0);
    vec4 tileColor = texture(lightMap, vec2(worldPosition.x / mapSize.x, worldPosition.y / mapSize.y));
    //vec2 normPixel = ivec2(gl_FragCoord) % 16;

    bool isOutOfWorld = (worldPosition.x > mapSize.x || worldPosition.x < 0) || (worldPosition.y > mapSize.y || worldPosition.y < 0);
    vec3 inTilePosition = vec3(fract(worldPosition.x) * tileSize, fract(worldPosition.y) * tileSize, 0);
    inTilePosition = vec3(inTilePosition.x / atlasSize.x, inTilePosition.y / atlasSize.y, 0);

//    float atlasOffsetX = tile.z * 255;
//    float atlasOffsetY = tile.w * 255;

    float atlasOffsetX = 0;
    float atlasOffsetY = 0;
    vec3 tileCoord = vec3( ((tileSize) / atlasSize.x),
                           ((tileSize) / atlasSize.y),
                            0);

    //Translate tileCoord by inTilePosition
    tileCoord = tileCoord + inTilePosition;

    //vec4 inAtlas = texelFetch(atlas, ivec2(tileCoord), 0);

    color = texture(atlas, vec3(0.5,0.5,0));

    //color = (!isOutOfWorld ? (texture(atlas, tileCoord)) : vec4(0.0f, 0.0f, 0.0f, 0.0f)) * clamp((texture(ambient, worldTime / 24.0f) +  tileColor), vec4(0.2f, 0.2f, 0.2f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
}