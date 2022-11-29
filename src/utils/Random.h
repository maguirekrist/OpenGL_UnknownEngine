//
// Created by magui on 11/5/2022.
//

#ifndef WORLD_CPP_RANDOM_H
#define WORLD_CPP_RANDOM_H

#include <random>

namespace Random {
    std::random_device dev;
    std::mt19937 rng(dev());

    template<typename T>
    T generate(T min, T max) {
        std::uniform_int_distribution<std::mt19937::result_type> dist6(min,max);

        return dist6(rng);
    }
}

#endif //WORLD_CPP_RANDOM_H
