//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_WORLD_H
#define ALPHAENGINECMAKE_WORLD_H


#include <vector>
#include "Tile.h"
#include "Texture.hpp"
#include "Light.hpp"

class World {
public:
    int width, height;
    std::vector<Tile> tiles;

    World() {}

    void generate(int width, int height);
    Texture generateWorldTexture();
    Texture generateWorldLightTexture(std::vector<Light> lights);
};


#endif //ALPHAENGINECMAKE_WORLD_H
