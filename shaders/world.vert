#version 330 core
layout (location = 0) in vec4 vertex;

out vec2 TexCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

//constants


void main() {
    //given vertex x,y we need to find out what tile it belongs to, starting from (0,0) to (1,1), should calculate a vec2 called tileCoord
//    vec2 tileCoord = calculateTileCoord(vec2(vertex.z, vertex.w));
    //Set TexCoord with the correct pixel with the tile we found the pixel belongs into, use code similar to this below:
    TexCoord = vertex.zw;
    gl_Position = projection * view * model * vec4(vertex.xy, 0.0, 1.0);
}