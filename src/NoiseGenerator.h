//
// Created by magui on 10/1/2022.
//

#ifndef WORLD_CPP_NOISEGENERATOR_H
#define WORLD_CPP_NOISEGENERATOR_H


#include <vector>
#include "INoiseGenerator.hpp"

class NoiseGenerator : public INoiseGenerator {
public:
    std::vector<int> generate(int dim) override;
};


#endif //WORLD_CPP_NOISEGENERATOR_H
