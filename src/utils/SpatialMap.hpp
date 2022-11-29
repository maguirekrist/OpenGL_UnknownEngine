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


    std::vector<T>& getBucket(const glm::ivec2& position);
    std::vector<T> getBucketCord(int x, int y);

    const std::vector<T>* tryGetBucket(const glm::ivec2& position);
    const std::vector<T> tryGetBucketMany(const glm::ivec2& position);
    bool exists(glm::ivec2 position);
    void insert(const glm::ivec2& position, T datum);
    void remove(glm::ivec2 position, T datum);
};

template<typename T>
std::vector<T>& SpatialMap<T>::getBucket(const glm::ivec2& position) {
    int x = (position.x / binWidth) % tableSize;
    int y = (position.y / binWidth) % tableSize;

    return table[y*tableSize + x];
}

template<typename T>
std::vector<T> SpatialMap<T>::getBucketCord(int x, int y) {

    if(x >= 0 && y >= 0 && (x < tableSize && y < tableSize)) {
        return table[y*tableSize + x];
    } else {
        return std::vector<T>{};
    }
}


template<typename T>
const std::vector<T>* SpatialMap<T>::tryGetBucket(const glm::ivec2& position)
{
    auto& bucket = getBucket(position);

    if(bucket.size() > 0)
    {
        return &bucket;
    } else {
        return nullptr;
    }
}

template<typename T>
const std::vector<T> SpatialMap<T>::tryGetBucketMany(const glm::ivec2& position) {
    //Calculate section of bin the tile is under
    int x = (position.x / binWidth) % tableSize;
    int y = (position.y / binWidth) % tableSize;

    int modX = position.x % binWidth;
    int modY = position.y % binWidth;
    int half = binWidth / 2;

    int dx = 0, dy = 0;

    //We know we are searching right
    if(modX >= half)
    {
        //right
        dx = 1;
    } else {
        //left
        dx = -1;
    }

    //We know we are searching top
    if(modY >= half)
    {
        //top
        dy = 1;
    } else {
        //bottom
        dy = -1;
    }

    //Use bucket overrides
    auto bucket1 = getBucketCord(x + dx, y);
    auto bucket2 = getBucketCord(x, y + dy);
    auto bucket3 = getBucketCord(x+ dx, y +dy);
    auto bucket = getBucket(position);

    std::vector<T> temp;
    temp.reserve(bucket1.size() + bucket2.size() + bucket3.size() + bucket.size());

    temp.insert(temp.end(), bucket.begin(), bucket.end());
    temp.insert(temp.end(), bucket1.begin(), bucket1.end());
    temp.insert(temp.end(), bucket2.begin(), bucket2.end());
    temp.insert(temp.end(), bucket3.begin(), bucket3.end());

    return temp;
}

template<typename T>
bool SpatialMap<T>::exists(glm::ivec2 position) {
    auto& bucket = getBucket(position);

    return bucket.size() > 0;
}

template<typename T>
void SpatialMap<T>::insert(const glm::ivec2& position, T datum) {
    auto& bucket = getBucket(position);

    bucket.push_back(datum);
}

template<typename T>
void SpatialMap<T>::remove(glm::ivec2 position, T datum)
{

}

#endif //ALPHAENGINECMAKE_SPATIALMAP_HPP
