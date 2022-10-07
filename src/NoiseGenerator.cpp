//
// Created by magui on 10/1/2022.
//

#include <random>
#include <iostream>
#include "NoiseGenerator.h"

//Precondition: Only works on square sizes
static void diamond_square(std::vector<int>& map, int chunk_size, int x1, int y1, int x2, int y2, float& roughness)
{
    int mapSize = std::sqrt(map.size());
    if((x2 - x1) <= 1 || (y2 - y1) <= 1)
        return;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(-2,2);

    int bottomLeft = map[(y1 * mapSize) + x1]; //bottomLeft
    int bottomRight = map[(y1 * mapSize) + x2]; //bottomRight

    int topRight = map[(y2 * mapSize) + x2]; //topRight
    int topLeft = map[(y2 * mapSize) + x1]; //topLeft

    int diamondValue = ((topLeft + topRight + bottomLeft + bottomRight) / 4) + (dist6(rng));


    int distance = (x2 - x1) / 2;
    int midX = ((x2 - x1) / 2) + x1;
    int midY = ((y2 - y1) / 2) + y1;

    //Diamond step
    map[(midY * mapSize) + midX] = diamondValue;




    //Square step
    //Branches off: 1. does there a exist a 4th vertex to draw weight from?
    //2. if not, we just take average of known points

    //farLeft
    float farLeft = x1 - distance < (mapSize - 1) ? map[(midY * mapSize) + x1 + distance] : map[(midY * mapSize) + x1 - distance];
    map[(midY * mapSize) + x1] = ((diamondValue + topLeft + bottomLeft + farLeft) / 4) + (dist6(rng)); //left

    float farRight = x2 + distance > (mapSize - 1) ? map[(midY * mapSize) + x2 - distance] : map[(midY * mapSize) + x2 + distance];
    map[(midY * mapSize) + x2] = ((diamondValue + bottomLeft + bottomRight + farRight) / 4) + (dist6(rng)); //right

    float farBottom = y1 - distance < (mapSize - 1) ? map[((y2 - distance) * mapSize) + midX] : map[((y1 - distance) * mapSize) + midX];
    map[(y1 * mapSize) + midX] = ((diamondValue + topLeft + topRight + farBottom) / 4) + (dist6(rng)); //bottom

    float farTop = y2 + distance > (mapSize - 1) ? map[((y1 + distance) * mapSize) + midX] : map[((y2 + distance) * mapSize) + midX];
    map[(y2 * mapSize) + midX] = ((diamondValue + topRight + bottomRight + farTop) / 4) + (dist6(rng)); //top

//    map[(midY * mapSize) + x1] = ((diamondValue + topLeft + bottomLeft) / 3.0f) + (dist6(rng) * roughness); //left
//    map[(midY * mapSize) + x2] = ((diamondValue + bottomLeft + bottomRight) / 3.0f) + (dist6(rng) * roughness); //right
//    map[(y1 * mapSize) + midX] = ((diamondValue + topLeft + topRight) / 3.0f) + (dist6(rng) * roughness); //bottom
//    map[(y2 * mapSize) + midX] = ((diamondValue + topRight + bottomRight) / 3.0f) + (dist6(rng) * roughness); //top


//WRONG MUST COMPLETE 1 STEP AT A TIME
//    diamond_square(map, x1, y1, midX, midY, roughness); //bottom_left sub
//    diamond_square(map, midX, y1, x2, midY, roughness); //bottom_right sub
//    diamond_square(map, x1, midY, midX, y2, roughness); //top_left sub
//    diamond_square(map, midX, midY, x2, y2, roughness); //top_right sub
    std::cout << "iteration" << std::endl;
}

//Precondition: Chunk size should be a area value
static void ds_generate(std::vector<int>& map, int chunk_size) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(-2,2);

    int mapSize = std::sqrt(map.size());
    int total_distance = std::sqrt(map.size());
    int distance  = std::sqrt(chunk_size) - 1;
    if(chunk_size < 2)
        return;

    //keep track of iteration
    //4^n represents number of iterations


    //Iterate through the chunks! Diamond Step
    for(int i = 0; i < total_distance - 1; i += distance)
    {
        int x1 = i;
        int x2 = i + distance;
        int y1 = i;
        int y2 = i + distance;
        //For each chunk, we need to compute the diamond step first
        int bottomLeft = map[(y1 * mapSize) + x1]; //bottomLeft
        int bottomRight = map[(y1 * mapSize) + x2]; //bottomRight

        int topRight = map[(y2 * mapSize) + x2]; //topRight
        int topLeft = map[(y2 * mapSize) + x1]; //topLeft

        int diamondValue = ((topLeft + topRight + bottomLeft + bottomRight) / 4) + (dist6(rng));

        int midX = ((x2 - x1) / 2) + x1;
        int midY = ((y2 - y1) / 2) + y1;

        //Diamond step
        map[(midY * mapSize) + midX] = diamondValue;
    }

    for(int i = 0; i < total_distance - 1; i += distance)
    {
        //for each chunk, we need to compute the square step
        int x1 = i;
        int x2 = i + distance;
        int y1 = i;
        int y2 = i + distance;
        int midX = ((x2 - x1) / 2) + x1;
        int midY = ((y2 - y1) / 2) + y1;
        int mid_distance = (x2-x1)/2;

        int diamondValue = map[(midY * mapSize) + midX];

        int bottomLeft = map[(y1 * mapSize) + x1]; //bottomLeft
        int bottomRight = map[(y1 * mapSize) + x2]; //bottomRight

        int topRight = map[(y2 * mapSize) + x2]; //topRight
        int topLeft = map[(y2 * mapSize) + x1]; //topLeft

        float farLeft = x1 - mid_distance < (mapSize - 1) ? map[(midY * mapSize) + x1 + mid_distance] : map[(midY * mapSize) + x1 - mid_distance];
        map[(midY * mapSize) + x1] = ((diamondValue + topLeft + bottomLeft + farLeft) / 4) + (dist6(rng)); //left

        float farRight = x2 + mid_distance > (mapSize - 1) ? map[(midY * mapSize) + x2 - mid_distance] : map[(midY * mapSize) + x2 + mid_distance];
        map[(midY * mapSize) + x2] = ((diamondValue + bottomLeft + bottomRight + farRight) / 4) + (dist6(rng)); //right

        float farBottom = y1 - mid_distance < (mapSize - 1) ? map[((y2 - mid_distance) * mapSize) + midX] : map[((y1 - mid_distance) * mapSize) + midX];
        map[(y1 * mapSize) + midX] = ((diamondValue + topLeft + topRight + farBottom) / 4) + (dist6(rng)); //bottom

        float farTop = y2 + mid_distance > (mapSize - 1) ? map[((y1 + mid_distance) * mapSize) + midX] : map[((y2 + mid_distance) * mapSize) + midX];
        map[(y2 * mapSize) + midX] = ((diamondValue + topRight + bottomRight + farTop) / 4) + (dist6(rng));
    }

    //recursive call to ds_generate but on smaller chunks
    //ds_generate(map, chunk_size / 4);
}

std::vector<int> NoiseGenerator::useDiamondSquare(int dim) {
    std::vector<int> heightMap(dim * dim, -999);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist6(1,8);
    //Step 1, initialize the corners
    float topLeft = dist6(rng);
    float topRight = dist6(rng);
    float bottomLeft = dist6(rng);
    float bottomRight = dist6(rng);

    float roughness = 7.0f;

    heightMap[(0 * dim) + 0] = bottomLeft; //bottomLeft
    heightMap[(0 * dim) + (dim-1)] = bottomRight; //bottomRight

    heightMap[((dim-1) * dim) + (dim-1)] = topRight; //topRight
    heightMap[((dim-1) * dim) + 0] = topLeft; //topLeft

    ds_generate(heightMap, heightMap.size());
    //heightMap[22] = 255;

    return heightMap;
}

