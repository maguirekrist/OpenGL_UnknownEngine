//
// Created by Maguire Krist on 11/1/22.
//

#ifndef ALPHAENGINECMAKE_TEXTUREARRAY_HPP
#define ALPHAENGINECMAKE_TEXTUREARRAY_HPP


#include "Texture.hpp"
#include <vector>

class TextureArray : public Texture {
public:
    //Constructor initializer list
    TextureArray(int dimension) : Texture(dimension) {}

    void insertTexture(Texture* text);

    void generate();
private:
    std::vector<Texture*> textures;
};


#endif //ALPHAENGINECMAKE_TEXTUREARRAY_HPP
