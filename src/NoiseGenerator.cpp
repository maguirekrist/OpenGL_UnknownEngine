//
// Created by magui on 10/1/2022.
//

#include <random>
#include "NoiseGenerator.h"

//Precondition: Only works on square sizes
static void diamond_square(std::vector<int>& map, int x1, int y1, int x2, int y2, float& roughness)
{
    int mapSize = std::sqrt(map.size());
    if((x2 - x1) <= 1 || (y2 - y1) <= 1)
        return;
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(-2,2);

    //At each iteration, the magnitude of the random variable should be multiplied by 2^-h, where h is a value between
    //0.0 and 0.1 (lower values produce rougher terrain)

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
    diamond_square(map, x1, y1, midX, midY, roughness); //bottom_left sub
    diamond_square(map, midX, y1, x2, midY, roughness); //bottom_right sub
    diamond_square(map, x1, midY, midX, y2, roughness); //top_left sub
    diamond_square(map, midX, midY, x2, y2, roughness); //top_right sub
}

std::vector<int> NoiseGenerator::useDiamondSquare(int dim) {
    std::vector<int> heightMap(dim * dim, 0);
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

    diamond_square(heightMap, 0, 0, dim - 1, dim - 1, roughness);

    return heightMap;
}

