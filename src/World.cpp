//
// Created by magui on 9/11/2022.
//

#include "World.h"
#include "Light.hpp"
#include "ResourceManager.hpp"
#include <random>
#include <glm/geometric.hpp>


static TileType compute_tile_type(int height_val)
{
    if(height_val < 4)
    {
        return TileType::Water;
    } else if(height_val >= 4 && height_val < 10) {
        return TileType::Terrain;
    } else if(height_val >= 10) {
        return TileType::Mountain;
    }

    return TileType::Terrain;
}

static void generate_texture_array(ArrayTexture& atlas, std::vector<std::pair<TileType, std::pair<std::string, int>>> tile_set)
{
    for(auto& tile : tile_set)
    {
        atlas.insertTexture(&ResourceManager::getTexture(tile.second.first));
    }
    atlas.generate();
}

World::World(int width, int height, int tileSize, Texture& ambient,
             std::unique_ptr<INoiseGenerator> &&generator) :
        width(width + 1),
        height(height + 1),
        tileSize(tileSize),
        spatialMap{(size_t)width/16, 16},
        ambient(ambient),
        heightMapGenerator(std::move(generator))
{

    ResourceManager::loadTexture("../resources/tiles/Soil.png", true, "soil", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/SoilRich.png", true, "soil_rich", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/SoftSand.png", true, "sand", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/RoughStone.png", true, "stone", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/WaterDeep.png", true, "water_deep", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/WaterShallow.png", true, "water_shallow", std::nullopt);

    tileOffsetMap[TileType::Water] = std::make_pair("water_deep", 0);
//    tileOffsetMap[TileType::WaterShallow] = std::make_pair("water_shallow", 1);

    tileOffsetMap[TileType::Terrain] = std::make_pair("soil", 1);
    tileOffsetMap[TileType::Mountain] = std::make_pair("stone", 2);
    tileOffsetMap[TileType::Wall] = std::make_pair("sand", 3);

    std::vector<std::pair<TileType, std::pair<std::string, int>>> temp(tileOffsetMap.begin(), tileOffsetMap.end());
    std::sort(temp.begin(), temp.end(), [](decltype(*std::begin(temp)) a, decltype(*std::end(temp)) b) {
        return a.second.second < b.second.second;
    });

    generate_texture_array(atlas,temp);

    generate();
}

//Generates procedural world based on height and width;
void World::generate() {
    this->heightMap = heightMapGenerator->generate(width);

    //Create matrix for columns
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            glm::vec2 position = glm::vec2(j, i);
            int tileHeight = this->heightMap[(i * height) + j];

            TileType tileType = compute_tile_type(tileHeight);

            tiles.emplace_back(Tile(tileOffsetMap[tileType].second, glm::tvec3<int>(position.x, position.y, tileHeight),  tileSize, tileSize, tileType));
        }
    }

    generateWorldTexture();
    generateWorldLightTexture();
}

void World::generateWorldTexture() {
    //Width x Height must equal the flat stream of bytes
    std::vector<std::uint8_t> tileData;
    tileData.reserve((this->width * this->height) * 4);

    for(auto iter : this->tiles){

//        if(iter.type == TileType::Wall)
//        {
//            std::cout << "there is a wall" << std::endl;
//            //ComputeTileBitmask(this, iter);
//        }

        tileData.push_back(iter.position.x);
        tileData.push_back(iter.position.y);

        //TODO: Determine offset now based on bitmap (however, this may not be done this way, we may use linear transitions in the shader for every tile)

        tileData.push_back(std::clamp((iter.position.z / 16.0f) * 255, 0.0f, 255.0f));
        tileData.push_back(iter.offset); //
    }

    Texture text;

    text.internal_format = GL_RGBA;
    text.image_format = GL_RGBA;
    text.nrChannels = 4;

    text.generate(this->width, this->height, tileData.data());
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
    text.nrChannels = 4;

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
