//
// Created by magui on 9/11/2022.
//

#include "World.h"
#include <random>

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