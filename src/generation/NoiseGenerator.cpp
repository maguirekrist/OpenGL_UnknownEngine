//
// Created by magui on 10/1/2022.
//

#include <random>
#include <ranges>
#include <algorithm>
#include <iostream>
#include "NoiseGenerator.h"
#include "../utils/Random.h"

//Precondition: Chunk size should be a area value
static void ds_generate(std::vector<int>& map, int count) {
    float magnitude_multiplier = std::pow(2, -(0.55 * count));

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(-10 * magnitude_multiplier,10 * magnitude_multiplier);

    int mapSize = std::sqrt(map.size());
    int iterations = std::pow(4, count);
    int squares_per_height = std::pow(2, count);

    int distance  = ((mapSize-1) / squares_per_height);

    if(distance <= 1)
        return;

    //keep track of iteration
    //4^n represents number of iterations

    //Iterate through the chunks! Diamond Step
    int yLevel = 0;
    int xLevel = 0;
    for(int i = 0; i < iterations; i++)
    {
        int x1 = xLevel * distance;
        int y1 = (yLevel * distance);

        int x2 = (xLevel+1) * distance;
        int y2 = (yLevel * distance) + distance;

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

        yLevel = xLevel == squares_per_height - 1 ? yLevel + 1 : yLevel;
        xLevel = xLevel == squares_per_height - 1 ? 0 : xLevel + 1;
    }


    yLevel = 0;
    xLevel = 0;
    for(int i = 0; i < iterations; i++)
    {
        int x1 = xLevel * distance;
        int y1 = (yLevel * distance);

        int x2 = (xLevel+1) * distance;
        int y2 = (yLevel * distance) + distance;

        int midX = ((x2 - x1) / 2) + x1;
        int midY = ((y2 - y1) / 2) + y1;
        int mid_distance = (x2-x1)/2;

        int diamondValue = map[(midY * mapSize) + midX];

        int bottomLeft = map[(y1 * mapSize) + x1]; //bottomLeft
        int bottomRight = map[(y1 * mapSize) + x2]; //bottomRight

        int topRight = map[(y2 * mapSize) + x2]; //topRight
        int topLeft = map[(y2 * mapSize) + x1]; //topLeft

        float farLeft = x1 - mid_distance < (mapSize - 1) ? map[(midY * mapSize) + x1 + mid_distance] : map[(midY * mapSize) + x1 - mid_distance];
        map[(midY * mapSize) + x1] = ((diamondValue + topLeft + bottomLeft + farLeft) / 4.0f) + (dist6(rng)); //left

        float farRight = x2 + mid_distance > (mapSize - 1) ? map[(midY * mapSize) + x2 - mid_distance] : map[(midY * mapSize) + x2 + mid_distance];
        map[(midY * mapSize) + x2] = ((diamondValue + bottomLeft + bottomRight + farRight) / 4) + (dist6(rng)); //right

        float farBottom = y1 - mid_distance < (mapSize - 1) ? map[((y2 - mid_distance) * mapSize) + midX] : map[((y1 - mid_distance) * mapSize) + midX];
        map[(y1 * mapSize) + midX] = ((diamondValue + topLeft + topRight + farBottom) / 4) + (dist6(rng)); //bottom

        float farTop = y2 + mid_distance > (mapSize - 1) ? map[((y1 + mid_distance) * mapSize) + midX] : map[((y2 + mid_distance) * mapSize) + midX];
        map[(y2 * mapSize) + midX] = ((diamondValue + topRight + bottomRight + farTop) / 4) + (dist6(rng));

        yLevel = xLevel == squares_per_height - 1 ? yLevel + 1 : yLevel;
        xLevel = xLevel == squares_per_height - 1 ? 0 : xLevel + 1;
    }

    //recursive call to ds_generate but on smaller chunks
    ds_generate(map, ++count);
}

static void median_filter(std::vector<int>& map, int kernel_size)
{
    int mapSize = std::sqrt(map.size());
    if (kernel_size >= mapSize) return;

    int edge = (kernel_size / 2);

    auto get_ordered_list = [&](int x, int y) -> std::vector<int> {
        std::vector<int> pixels;

        for (int i = 0; i < kernel_size; i++) {
            for (int j = 0; j < kernel_size; j++) {
                pixels.push_back(map[(mapSize * (y+i-edge)) + (x+j-edge)]);
            }
        }

        std::ranges::sort(pixels);

        return pixels;
    };

    //start at kernel_size to avoid border issue with kernel filter
    for (int i = edge; i < (mapSize - edge); i++) {
        for (int j = edge; j < (mapSize - edge); j++) {
            //construct an ordered list of the pixels in the kernel window
            auto olist = get_ordered_list(j, i);
            map[(mapSize * i) + j] = olist[olist.size() / 2]; //set the pixel to the media value
        }
    }

}


std::vector<int> NoiseGenerator::generate(int dim) {
    std::vector<int> heightMap(dim * dim, -999);

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist6(0, 22);

    //Step 1, initialize the corners
    auto topLeft = dist6(rng);
    auto topRight = dist6(rng);
    auto bottomLeft = dist6(rng);
    auto bottomRight = dist6(rng);


    heightMap[(0 * dim) + 0] = bottomLeft; //bottomLeft
    heightMap[(0 * dim) + (dim-1)] = bottomRight; //bottomRight

    heightMap[((dim-1) * dim) + (dim-1)] = topRight; //topRight
    heightMap[((dim-1) * dim) + 0] = topLeft; //topLeft

    ds_generate(heightMap, 0);
    median_filter(heightMap, 3);
    //heightMap[22] = 255;


    std::cout << "max height in map: " << *std::max_element(heightMap.begin(), heightMap.end()) << std::endl;
    std::cout << "min height in map: " << *std::min_element(heightMap.begin(), heightMap.end()) << std::endl;
    return heightMap;
}

