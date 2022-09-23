//
// Created by magui on 9/11/2022.
//

#include "World.h"
#include "Light.hpp"
#include <random>
#include <glm/geometric.hpp>
#include <Tracy.hpp>

//Generates procedural world based on height and width;
void World::generate(int width, int height) {
    this->width = width;
    this->height = height;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,3);

    //Create matrix for columns
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            float rand = dist6(rng);
            glm::vec2 offset = glm::vec2(0.0f, 7.0f + rand);
            glm::vec2 position = glm::vec2(j, i);
            tiles.emplace_back(Tile(offset, position,  16, 16));
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
        stuff.push_back(iter.offsetX);
        stuff.push_back(iter.offsetY);
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
    ZoneScoped;
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
    ZoneScoped;
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

void World::addLight(Light light) {
    spatialMap.insert(light.position, light);
    updateWorldLightTexture(light);
}