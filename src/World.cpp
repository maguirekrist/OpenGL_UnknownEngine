//
// Created by magui on 9/11/2022.
//

#include "World.h"
#include "Light.hpp"
#include <random>
#include <glm/geometric.hpp>


const std::vector<glm::vec2> tileOffsets
        {
                { 0.0f, 6.0f},
                { 0.0f, 0.0f },
                { 0.0f, 1.0f }
        };

const int TILE_DIM = 8;

static TileType compute_tile_type(int height_val)
{
    if(height_val < 4)
    {
        return TileType::Water;
    } else if(height_val > 4 && height_val < 10) {
        return TileType::Terrain;
    } else {
        return TileType::Mountain;
    }
}

//Generates procedural world based on height and width;
void World::generate(int width, int height) {
    this->width = width;
    this->height = height;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(0,3);

    this->heightMap = heightMapGenerator->generate(width+1);

    //Create matrix for columns
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            glm::vec2 position = glm::vec2(j, i);
            TileType tileType = compute_tile_type(this->heightMap[i * height + j]);
            tiles.emplace_back(Tile(tileOffsets[static_cast<int>(tileType)], position,  TILE_DIM, TILE_DIM, tileType));
        }
    }

    generateWorldTexture();
    generateWorldLightTexture();
}

void World::generateWorldTexture() {
    //Width x Height must equal the flat stream of bytes
    std::vector<std::uint8_t> stuff;
    stuff.reserve((this->width * this->height) * 4);


    for(auto iter : this->tiles){
        stuff.push_back(iter.position.x);
        stuff.push_back(iter.position.y);

        if(iter.type == TileType::Wall)
        {
            std::cout << "there is a wall" << std::endl;
            //ComputeTileBitmask(this, iter);
        }
        //Determine offset now based on bitmap
        stuff.push_back(iter.offset.x);
        stuff.push_back(iter.offset.y);
    }

    Texture text;

    text.internal_format = GL_RGBA;
    text.image_format = GL_RGBA;

    text.generate(this->width, this->height, stuff.data());
    tileMap = text;
}


float World::sumWorldLights(const std::vector<Light> &lights, glm::vec2 pos) {
    float value = 0.0f;
    for(int i = 0; i < lights.size(); i++)
    {
        float distance = glm::distance(pos, glm::vec2(lights[i].position.x, lights[i].position.y));
        value += std::clamp((-distance * 32) + 255, 0.0f, 255.0f);
    }

    return value;
}

void World::generateWorldLightTexture() {
    //Width x Height must equal the flat stream of bytes
    std::vector<std::uint8_t> stuff;
    glm::vec2 center = glm::vec2(this->width / 2, this->height / 2);

    float ambient = 40.0f;

    stuff.reserve((this->width * this->height) * 4);

    for(auto iter : this->tiles){
        float value = (0.0f + ambient);
        const std::vector<Light>* lights = spatialMap.tryGetBucket(iter.position);

        if(lights)
        {
            value = sumWorldLights(*lights, iter.position);
            value = std::clamp(value + ambient, 0.0f, 255.0f);
        }

        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(value);
    }


    Texture text;

    text.internal_format = GL_RGBA;
    text.image_format = GL_RGBA;

    text.mag_filter = GL_LINEAR;

    text.generate(this->width, this->height, stuff.data());

    lightMapImage = stuff;
    lightMap = text;
}

void World::updateWorldLightTexture(const Light &light) {
    float ambient = 40.0f;
    //const int channel_size = 4;
    int diameter = (light.radius * 2);//we use RGBA 4 byte channel for textures, if this changes to be a singular byte or something, update this value and everything should still work
    //int lightCenter = (light.position.x * light.position.y)*channel_size;//4 being the number of bytes in the
    int start_x = std::clamp((int)(light.position.x - light.radius), 0, width);
    int start_y = std::clamp((int)(light.position.y - light.radius), 0, height);
    int end_y = std::clamp((start_y + diameter), 0, height);
    int start = (start_y * height + start_x);

    // how many iterations we do per skip
    //int texture_width = width * channel_size;

    int skip = std::abs((diameter + start) - width); //how much to skip in the iteration

    std::vector<Tile>::iterator tilePtr;

    for(int y = 0; y < diameter; y++)
    {
        auto newStart = tiles.begin() + (start + (height * y));
        for(tilePtr = newStart; tilePtr < newStart + diameter; tilePtr++) {
            float value = (0.0f + ambient);
            const std::vector<Light> lights = spatialMap.tryGetBucketMany(tilePtr->position);

            value = sumWorldLights(lights, tilePtr->position);
            value = std::clamp(value + ambient, 0.0f, 255.0f);

            int inPos = (int)((tilePtr->position.y * height + tilePtr->position.x)*4);

            lightMapImage[inPos] = static_cast<std::uint8_t>(value);
            lightMapImage[inPos+1] = static_cast<std::uint8_t>(value);
            lightMapImage[inPos+2] = static_cast<std::uint8_t>(value);
            lightMapImage[inPos+3] = static_cast<std::uint8_t>(value);
        }
    }

    lightMap.generate(width, height, lightMapImage.data());

//
//    std::vector<std::uint8_t>::iterator ptr;
//
//    for(int y = start_y; y < (start_y + light.radius); y++)
//    {
//        for(ptr = lightMapImage.begin() + (start + (skip * y)); ptr < lightMapImage.begin() + diameter; ptr++) {
//
//        }
//    }

}

void World::tickWorldTime(double dt) {
    tickAccumulator += dt;
    if(tickAccumulator >= 1){
        worldTime += 1.0f / 60.0f;
        tickAccumulator = 0;
    }
}

void World::addLight(Light light) {
    spatialMap.insert(light.position, light);
    updateWorldLightTexture(light);
}

void World::placeTile(Tile tile) {
    tiles[height * tile.position.y + tile.position.x] = tile;
    generateWorldTexture();
}