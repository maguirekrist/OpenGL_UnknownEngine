//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_WORLD_H
#define ALPHAENGINECMAKE_WORLD_H


#include <vector>
#include "Tile.h"
#include "Texture.hpp"

class World {
public:
    int width, height;
    std::vector<Tile> tiles;

    World() {}

    void generate(int width, int height);
    Texture generateWorldTexture();
};


#endif //ALPHAENGINECMAKE_WORLD_H
