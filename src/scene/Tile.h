//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_TILE_H
#define ALPHAENGINECMAKE_TILE_H


#include <glm/vec2.hpp>
#include <glm/detail/type_vec3.hpp>
#include "../utils/TileType.h"

class Tile {
public:
    int width, height;
    TileType type;

    std::uint8_t bitmask = 0;

    glm::tvec3<int> position; //x, y, then z representing tile height in the heightMap

    int offset;

    Tile(int offset, glm::tvec3<int> position, int width, int height, TileType type) :
        offset(offset),
        position(position),
        width(width),
        height(height),
        type(type)
        {}

};


#endif //ALPHAENGINECMAKE_TILE_H
