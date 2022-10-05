//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_TILE_H
#define ALPHAENGINECMAKE_TILE_H


#include <glm/vec2.hpp>
#include "utils/TileType.h"

class Tile {
public:
    int offsetY, offsetX;
    int width, height;
    TileType type = TileType::terrain;

    std::uint8_t bitmask = 0;

    glm::ivec2 position;

    Tile(glm::ivec2 offset, glm::ivec2 position, int width, int height, TileType type) :
        offsetY(offset.y),
        offsetX(offset.x),
        position(position),
        width(width),
        height(height),
        type(type)
        {}
};


#endif //ALPHAENGINECMAKE_TILE_H
