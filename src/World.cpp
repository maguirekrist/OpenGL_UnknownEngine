//
// Created by magui on 9/11/2022.
//

#include "World.h"
#include "Light.hpp"
#include <random>
#include <glm/geometric.hpp>


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
            tiles.emplace_back(Tile("container", offset, position,  16, 16));
        }
    }
}

Texture World::generateWorldTexture() {
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
    return text;
}

const Light* World::findNearestLight(const std::vector<Light>& lights, glm::vec2 pos) {

    float distance;
    const Light* target = nullptr;


    for(int i = 0; i < lights.size(); i++) {
        float temp = glm::distance(pos,  lights[i].position);

        if(i == 0)
            distance = std::abs(temp);

        if(std::abs(temp) <= distance) {
            distance = std::abs(temp); //store shortest distance
            target = &lights[i];
        }
    }

    return target;
}

float World::sumWorldLights(const std::vector<Light> &lights, glm::vec2 pos) {
    float value = 0.0f;
    for(int i = 0; i < lights.size(); i++)
    {
        float distance = glm::distance(pos, lights[i].position);
        value += std::clamp((-distance * 32) + 255, 0.0f, 255.0f);
    }

    return value;
}

Texture World::generateWorldLightTexture() {
    //Width x Height must equal the flat stream of bytes

    std::vector<std::uint8_t> stuff;
    glm::vec2 center = glm::vec2(this->width / 2, this->height / 2);

    float ambient = 40.0f;

    stuff.reserve((this->width * this->height) * 4);

    auto start = std::chrono::steady_clock::now();
    for(auto iter : this->tiles){
        float value = (0.0f + ambient);

        if(spatialMap.exists(iter.position)) {
//            const Light* nearestLight = findNearestLight(spatialMap.getBucket(iter.position), iter.position);
//            float distance = std::abs(glm::distance(iter.position, nearestLight->position));
//            //find nearest tile
//            if(nearestLight->radius >= distance) {
//                value = std::clamp((-distance * 32) + 255, 0.0f, 255.0f);
//                value = std::clamp(value + ambient, 0.0f, 255.0f);
//            }

            value = sumWorldLights(spatialMap.getBucket(iter.position), iter.position);
            value = std::clamp(value + ambient, 0.0f, 255.0f);
        }
        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(value);
    }
    auto end = std::chrono::steady_clock::now();
    auto time = end - start;
    std::cout << "Time to generate texture in miliseconds -> " << std::chrono::duration_cast<std::chrono::microseconds>(time).count() << std::endl;


    Texture text;

    text.internal_format = GL_RGBA;
    text.image_format = GL_RGBA;

    text.mag_filter = GL_LINEAR;

    text.generate(this->width, this->height, stuff.data());

    return text;
}

void World::addLight(Light light) {
    spatialMap.insert(light.position, light);
}