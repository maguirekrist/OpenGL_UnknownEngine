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

uniform vec3 selectTile;

const int tileSize = 1024; //this seems to control the resolution of the tiles


//Easing function, however, I don't think this is working correctly for anything but x;
float easeInQuad(float x) {
    return smoothstep(0.2,0.8,x);
}


vec4 biLerp(vec4 a, vec4 b, vec4 c, vec4 d, float s, float t)
{
    vec4 x = mix(a, b, easeInQuad(t));
    vec4 y = mix(c, d, easeInQuad(t));
    return mix(x,y, easeInQuad(s));
}

void main()
{
    vec2 mapSize = textureSize(tileMap, 0);
    vec3 atlasSize = textureSize(atlas, 0); //returns width, height, and depth of texture array

    //Tile here represents a 1 tile in the aTexture tile map, x, y is tile position, z, w is offset into atlas
    vec2 worldPosition = vec2(view * vec4(gl_FragCoord.xy, 0, 1));

    vec4 tile = texelFetch(tileMap, ivec2(worldPosition), 0);

    //tileDiffuse
    vec4 tileColor = texture(lightMap, vec2(worldPosition.x / mapSize.x, worldPosition.y / mapSize.y));
    bool isOutOfWorld = (worldPosition.x > mapSize.x || worldPosition.x < 0) || (worldPosition.y > mapSize.y || worldPosition.y < 0);

    vec2 texCoord = fract(worldPosition.xy);
    vec2 shiftedWorldPosition = worldPosition.xy - vec2(0.5);
    ivec2 baseTile = ivec2(shiftedWorldPosition);
    vec2 bilerpFactors = fract(shiftedWorldPosition);

    float aW = texelFetch(tileMap, baseTile, 0).w;
    float bW = texelFetch(tileMap, baseTile + ivec2(1,0), 0).w;
    float cW = texelFetch(tileMap, baseTile + ivec2(0,1), 0).w;
    float dW = texelFetch(tileMap, baseTile + ivec2(1,1), 0).w;

    vec4 aColor = texture(atlas, vec3(texCoord, aW * 255));
    vec4 bColor = texture(atlas, vec3(texCoord, bW * 255));
    vec4 cColor = texture(atlas, vec3(texCoord, cW * 255));
    vec4 dColor = texture(atlas, vec3(texCoord, dW * 255));

    vec4 outColor = biLerp(
            aColor,
            bColor,
            cColor,
            dColor,
            bilerpFactors.y,
            bilerpFactors.x
    );

    if(ivec2(vec4(selectTile.xy, 0.0f, 1.0f).xy) == ivec2(worldPosition))
        outColor = (outColor * 0.6f) + (vec4(1.0f, 1.0f, 1.0f, 1.0f) * (1 - 0.6f));

    if(!heightMapView)
        color = (!isOutOfWorld ? vec4(outColor.xyz, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 0.0f)) * clamp((texture(ambient, worldTime / 24.0f) +  tileColor), vec4(0.2f, 0.2f, 0.2f, 0.2f), vec4(1.0f, 1.0f, 1.0f, 1.0f));
    else
        color = (!isOutOfWorld ? vec4(tile.z, tile.z, tile.z, 1.0f) : vec4(0.0f, 0.0f, 0.0f, 0.0f));
}