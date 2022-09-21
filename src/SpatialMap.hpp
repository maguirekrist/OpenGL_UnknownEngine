//
// Created by Maguire Krist on 9/21/22.
//

#ifndef ALPHAENGINECMAKE_SPATIALMAP_HPP
#define ALPHAENGINECMAKE_SPATIALMAP_HPP


#include <cstddef>
#include <vector>
#include <glm/vec2.hpp>

template<typename T>
class SpatialMap {
public:
    size_t tableSize; // number of bins in each axis
    size_t binWidth; // size of bin
    std::vector<std::vector<T>> table;

    SpatialMap(size_t tSize, size_t binSize) : tableSize(tSize), binWidth(binSize) {
        table.reserve(tSize * tSize);

        for(int i = 0; i < tableSize * tableSize; i++)
        {
            table.push_back(std::vector<T>{});
        }
    };


    const std::vector<T>& getBucket(const glm::ivec2& position);
    const std::vector<T>* tryGetBucket(const glm::ivec2& position); //TODO
    bool exists(glm::ivec2 position);
    void insert(glm::ivec2 position, T datum);
    void remove(glm::ivec2 position, T datum);
};

template<typename T>
const std::vector<T>& SpatialMap<T>::getBucket(const glm::ivec2& position) {
    int x = (position.x / binWidth) % tableSize;
    int y = (position.y / binWidth) % tableSize;

    return table[y*tableSize + x];
}

template<typename T>
const std::vector<T>* tryGetBucket(const glm::ivec2& position)
{
    //TODO: GOAL ~ use this function to return a vector of entities that may effect a given ivec2 position.
    //We can assume that lights at a limit radius of effect, so really, we shouldn't need to scan for many nearby quadrants
    return nullptr;
}

template<typename T>
bool SpatialMap<T>::exists(glm::ivec2 position) {
    auto& bucket = getBucket(position);

    return bucket.size() > 0;
}

template<typename T>
void SpatialMap<T>::insert(glm::ivec2 position, T datum) {
    auto& bucket = getBucket(position);

    bucket.push_back(datum);
}

template<typename T>
void SpatialMap<T>::remove(glm::ivec2 position, T datum)
{

}

#endif //ALPHAENGINECMAKE_SPATIALMAP_HPP
