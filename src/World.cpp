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
    for(auto iter : this->tiles){
        stuff.push_back(iter.position.x);
        stuff.push_back(iter.position.y);
        stuff.push_back(iter.offsetX);
        stuff.push_back(iter.offsetY);
    }

    std::cout << (int)stuff[2] << " " << (int)stuff[3] << std::endl;

    Texture text;



    text.internal_format = GL_RGBA;
    text.image_format = GL_RGBA;

    text.generate(this->width, this->height, stuff.data());
    return text;
}

static Light findNearestLight(std::vector<Light> lights, glm::vec2 pos) {

    float distance;
    Light *target;

    for(int i = 0; i < lights.size(); i++) {
        float temp = glm::distance(pos,  lights[i].position);

        if(i == 0)
            distance = std::abs(temp);

        if(std::abs(temp) <= distance) {
            distance = std::abs(temp); //store shortest distance
            target = &lights[i];
        }
    }

    return *target;
}

Texture World::generateWorldLightTexture(std::vector<Light> lights) {
    //Width x Height must equal the flat stream of bytes
    std::vector<std::uint8_t> stuff;
    glm::vec2 center = glm::vec2(this->width / 2, this->height / 2);

    float ambient = 40.0f;

    for(auto iter : this->tiles){
        float value = (0.0f + ambient);
        Light nearestLight = findNearestLight(lights, iter.position);
        float distance = std::abs(glm::distance(iter.position, nearestLight.position));
        //find nearest tile
        if(nearestLight.radius >= distance) {
            value = std::clamp((-distance * 32) + 255, 0.0f, 255.0f);
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
    return text;
}