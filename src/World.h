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
#include "INoiseGenerator.hpp"

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
    double worldTime;
    std::vector<Tile> tiles;
    SpatialMap<Light> spatialMap;
    std::vector<std::uint8_t> lightMapImage;
    std::vector<int> heightMap;

    Texture lightMap;
    Texture ambient;
    Texture tileMap;
    Texture atlas;

    std::unique_ptr<INoiseGenerator> heightMapGenerator;

    World(int width, int height, Texture atlas, Texture ambient, std::unique_ptr<INoiseGenerator>&& generator) :
        width(width),
        height(height),
        spatialMap{(size_t)width/16, 16},
        atlas(atlas),
        ambient(ambient),
        heightMapGenerator(std::move(generator)) {}

    void generate(int width, int height);
    void addLight(Light light);
    void placeTile(Tile tile);
    void generateWorldTexture();
    void generateWorldLightTexture();
    void tickWorldTime(double dt);
private:
    double tickAccumulator;

    float sumWorldLights(std::vector<Light> const& lights, glm::vec2);
    void updateWorldLightTexture(const Light& light);

friend std::uint8_t ComputeTileBitmask(const World* world, Tile& tile);
};

//std::uint8_t ComputeTileBitmask(const World* world, Tile& tile) {
//    std::uint8_t mask = 0;
//
//    //compute 4 boolean checks on the left, top, right, and bottom of tile
//    if(world->tiles[(world->height * (tile.position.y + 1)) + tile.position.x].type == tile.type) // Tile above
//        mask += 1;
//    if(world->tiles[(world->height * (tile.position.y - 1)) + tile.position.x].type == tile.type) // Tile below
//        mask += 8;
//    if(world->tiles[(world->height * (tile.position.y)) + tile.position.x + 1].type == tile.type) //Tile right
//        mask += 4;
//    if(world->tiles[(world->height * (tile.position.y)) + tile.position.x - 1].type == tile.type) // Tile left
//        mask += 2;
//
//    std::unordered_map<uint8_t, glm::ivec2> offsetMap;
//    offsetMap[0] = glm::ivec2(5, 4);
//    offsetMap[1] = glm::ivec2(5, 5);
//    offsetMap[2] = glm::ivec2(4, 6);
//    offsetMap[3] = glm::ivec2(5, 4);
//
//    //mask can now have a total of 16 combinations, we need to map those 16 values to a offset position on our atlas
//    //this is hardcoded for now, but should be refactored to be more dynamic to reference a config file or something
//    return mask;
//}


#endif //ALPHAENGINECMAKE_WORLD_H
