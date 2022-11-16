#version 330 core

out vec4 color;

uniform sampler2D tileMap;
uniform sampler2DArray atlas; //because atlas is now a Texture array we need the proper sampler type for that

uniform sampler2D lightMap;
uniform sampler1D ambient; //1D gradient texture that is used for day-night changes


uniform mat4 view; //Matrix is responsible for converting screen coord (gl_FragCoord) to world coodinates.
                    //View will also translate and scale world (scroll/zoom)
uniform float worldTime; // This value is used to sample ambientGradient to color our world for day/night cycle
uniform bool heightMapView;

const int tileSize = 1024; //this seems to control the resolution of the tiles

void main()
{
    vec2 mapSize = textureSize(tileMap, 0);
    vec3 atlasSize = textureSize(atlas, 0); //returns width, height, and depth of texture array
    //vec3 atlasSize = vec3(1024, 1024, 0);

    //Tile here represents a 1 tile in the aTexture tile map, x, y is tile position, z, w is offset into atlas
    vec2 worldPosition = vec2(view * vec4(gl_FragCoord.xy, 0, 1));
    vec4 tile = texelFetch(tileMap, ivec2(worldPosition), 0);
    vec2 tilePosition;
    modf(worldPosition, tilePosition);

    //tileDiffuse
    //vec4 tileColor = texelFetch(lightMap, ivec2(worldPosition), 0);
    vec4 tileColor = texture(lightMap, vec2(worldPosition.x / mapSize.x, worldPosition.y / mapSize.y));
    //vec2 normPixel = ivec2(gl_FragCoord) % 16;

    bool isOutOfWorld = (worldPosition.x > mapSize.x || worldPosition.x < 0) || (worldPosition.y > mapSize.y || worldPosition.y < 0);

    vec3 inTilePosition = vec3(fract(worldPosition.x) * tileSize, fract(worldPosition.y) * tileSize, 0);
    inTilePosition = vec3(inTilePosition.x / atlasSize.x, inTilePosition.y / atlasSize.y, 0);


    //Interpolation Code
    //1. get the 4 corner tiles, sample in them just like you do below
    vec4 tile_top_left = texelFetch(tileMap, ivec2(clamp(worldPosition.x - 1, 0, mapSize.x), clamp(worldPosition.y + 1, 0, mapSize.y)), 0);
    vec4 tile_top_right = texelFetch(tileMap, ivec2(clamp(worldPosition.x + 1, 0, mapSize.x), clamp(worldPosition.y + 1, 0, mapSize.y)), 0);
    vec4 tile_bottom_right = texelFetch(tileMap, ivec2(clamp(worldPosition.x + 1, 0, mapSize.x), clamp(worldPosition.y - 1, 0, mapSize.y)), 0);
    vec4 tile_bottom_left = texelFetch(tileMap, ivec2(clamp(worldPosition.x - 1, 0, mapSize.x), clamp(worldPosition.y - 1, 0, mapSize.y)), 0);

    //2. mix between colors
    vec4 origin_color = texture(atlas, vec3(inTilePosition.xy, tile.w * 255));
    vec4 color_tl = texture(atlas, vec3(inTilePosition.xy, tile_top_left.w * 255));
    vec4 color_tr = texture(atlas, vec3(inTilePosition.xy, tile_top_right.w * 255));
    vec4 color_br = texture(atlas, vec3(inTilePosition.xy, tile_bottom_right.w * 255));
    vec4 color_bl = texture(atlas, vec3(inTilePosition.xy, tile_bottom_left.w * 255));


    vec4 outColor = (
        mix(color_tl, origin_color, (tile_top_left.w > tile.w ? distance(vec2(tilePosition.x, tilePosition.y+1), vec2(tilePosition.x + inTilePosition.x, tilePosition.y + inTilePosition.y)) : 1.0f))
        + mix(color_tr, origin_color, (tile_top_right.w > tile.w ? distance(vec2(tilePosition.x+1, tilePosition.y+1), vec2(tilePosition.x + inTilePosition.x, tilePosition.y + inTilePosition.y)) : 1.0f))
    ) / 2;


    //color = texture(atlas, vec3(0.5,0.5,0));
    if(!heightMapView)
        color = (!isOutOfWorld ? outColor : vec4(0.0f, 0.0f, 0.0f, 0.0f)) * clamp((texture(ambient, worldTime / 24.0f) +  tileColor), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else
        color = (!isOutOfWorld ? vec4(tile.z, tile.z, tile.z, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 0.0f));
}