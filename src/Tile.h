//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_TILE_H
#define ALPHAENGINECMAKE_TILE_H


#include <glm/vec2.hpp>

class Tile {
public:
    int offsetY, offsetX;
    const char* atlas;
    int width, height;

    glm::vec2 position;

    Tile(const char* atlas, glm::vec2 offset, glm::vec2 position, int width, int height) :
        atlas(atlas),
        offsetY(offset.y),
        offsetX(offset.x),
        position(position),
        width(width),
        height(height)
        {}
};


#endif //ALPHAENGINECMAKE_TILE_H
