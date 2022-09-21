//
// Created by magui on 9/11/2022.
//

#ifndef ALPHAENGINECMAKE_WORLD_H
#define ALPHAENGINECMAKE_WORLD_H


#include <vector>
#include <unordered_map>
#include <functional>
#include "Tile.h"
#include "Texture.hpp"
#include "Light.hpp"
#include "SpatialMap.hpp"

//const int BUCKET_SIZE = 16;
//
//struct SpatialMap {
//    std::size_t operator()(const glm::vec2& k) const {
//        double x , y;
//        std::modf(k.x / BUCKET_SIZE, &x);
//        std::modf(k.y / BUCKET_SIZE, &y);
//
//        return std::hash<int>()((int)x ^  (int)y);
//    }
//};

class World {
public:
    int width = 256, height = 256;
    std::vector<Tile> tiles;
    SpatialMap<Light> spatialMap;

    World(int width, int height) : width(width), height(height), spatialMap{(size_t)width/16, 16} {}

    void generate(int width, int height);
    void addLight(Light light);
    Texture generateWorldTexture();
    Texture generateWorldLightTexture();
private:
    const Light* findNearestLight(const std::vector<Light>& lights, glm::vec2 pos);
    float sumWorldLights(std::vector<Light> const& lights, glm::vec2);
};


#endif //ALPHAENGINECMAKE_WORLD_H
