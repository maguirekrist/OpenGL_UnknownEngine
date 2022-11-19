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


float easeInQuad(float x) {
    return x * x;
}


vec4 biLerp(vec4 a, vec4 b, vec4 c, vec4 d, float s, float t)
{
    vec4 x = mix(a, b, easeInQuad(t));
    vec4 y = mix(c, d, easeInQuad(t));
    return mix(x,y,easeInQuad(s));
}

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


    vec4 tile_left = texelFetch(tileMap, ivec2(clamp(worldPosition.x - 1, 0, mapSize.x), clamp(worldPosition.y, 0, mapSize.y)), 0);
    vec4 tile_bottom = texelFetch(tileMap, ivec2(clamp(worldPosition.x, 0, mapSize.x), clamp(worldPosition.y - 1, 0, mapSize.y)), 0);
    vec4 tile_right = texelFetch(tileMap, ivec2(clamp(worldPosition.x + 1, 0, mapSize.x), clamp(worldPosition.y, 0, mapSize.y)), 0);
    vec4 tile_top = texelFetch(tileMap, ivec2(clamp(worldPosition.x, 0, mapSize.x), clamp(worldPosition.y + 1, 0, mapSize.y)), 0);


    //2. mix between colors
    vec4 origin_color = texture(atlas, vec3(inTilePosition.xy, tile.w * 255));
    vec4 color_tl = texture(atlas, vec3(inTilePosition.xy, tile_top_left.w * 255));
    vec4 color_tr = texture(atlas, vec3(inTilePosition.xy, tile_top_right.w * 255));
    vec4 color_br = texture(atlas, vec3(inTilePosition.xy, tile_bottom_right.w * 255));
    vec4 color_bl = texture(atlas, vec3(inTilePosition.xy, tile_bottom_left.w * 255));

    vec4 color_l = texture(atlas, vec3(inTilePosition.xy, tile_left.w * 255));
    vec4 color_r = texture(atlas, vec3(inTilePosition.xy, tile_right.w * 255));
    vec4 color_b = texture(atlas, vec3(inTilePosition.xy, tile_bottom.w * 255));
    vec4 color_t = texture(atlas, vec3(inTilePosition.xy, tile_top.w * 255));

    vec4 outColor = biLerp(
            tile_top_left.w < tile.w ? color_tl : origin_color,
            tile_top_right.w < tile.w ? color_tr : origin_color,
            tile_bottom_left.w < tile.w ? color_bl : origin_color,
            tile_bottom_right.w < tile.w ? color_br : origin_color,
            (-inTilePosition.y + 1.0f),// relative position on the "vertical" axis between a and b, or c a3nd d.
            inTilePosition.x); // relative position on the "horizontal" axis between a and c, or b and d.

//    vec4 outColor = origin_color;

//    if(tile_bottom.w < tile.w)
//        outColor = mix(color_b, origin_color, tile_bottom.w < tile.w ? inTilePosition.y : 1.0f);
//
//    if(tile_right.w < tile.w)
//        outColor = mix(color_r, origin_color, tile_right.w < tile.w ? -inTilePosition.x + 1.0f : 1.0f);
//
//    if(tile_top.w < tile.w)
//        outColor = mix()

//    vec4 outColor = biLerp(
//        tile_left.w < tile.w ? color_l : origin_color,
//        tile_right.w < tile.w ? color_r : origin_color,
//        tile_bottom.w < tile.w ? color_b : origin_color,
//        tile_top.w < tile.w ? color_t : origin_color,
//        -inTilePosition.y + 1.0f,// relative position on the "vertical" axis between a and b, or c and d.
//        inTilePosition.x);

    //    vec4 outColor = (
//        mix(color_tl, origin_color, (tile_top_left.w > tile.w ? distance(vec2(tilePosition.x, tilePosition.y+1), vec2(tilePosition.x + inTilePosition.x, tilePosition.y + inTilePosition.y)) : 1.0f))
//    );

    //color = texture(atlas, vec3(0.5,0.5,0));
    if(!heightMapView)
        color = (!isOutOfWorld ? outColor : vec4(0.0f, 0.0f, 0.0f, 0.0f)) * clamp((texture(ambient, worldTime / 24.0f) +  tileColor), vec4(1.0f, 1.0f, 1.0f, 1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else
        color = (!isOutOfWorld ? vec4(tile.z, tile.z, tile.z, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 0.0f));
}