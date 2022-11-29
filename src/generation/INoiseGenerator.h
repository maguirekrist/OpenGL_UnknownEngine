//
// Created by Maguire Krist on 10/14/22.
//

#ifndef ALPHAENGINECMAKE_INOISEGENERATOR_HPP
#define ALPHAENGINECMAKE_INOISEGENERATOR_HPP


#include <vector>

class INoiseGenerator {
public:
    virtual std::vector<int> generate(int dim) = 0;

};


#endif //ALPHAENGINECMAKE_INOISEGENERATOR_HPP
