//
// Created by Maguire Krist on 11/1/22.
//

#ifndef ALPHAENGINECMAKE_TEXTUREARRAY_HPP
#define ALPHAENGINECMAKE_TEXTUREARRAY_HPP


#include "Texture.hpp"
#include <vector>

class ArrayTexture : public Texture {
public:
    //Constructor initializer list
    ArrayTexture() : Texture(GL_TEXTURE_2D_ARRAY) {}
    explicit ArrayTexture(int dimension) : Texture(dimension) {}

    void insertTexture(Texture* text);

    void generate();
private:
    int m_width;
    int m_height;

    std::vector<Texture*> textures;
};


#endif //ALPHAENGINECMAKE_TEXTUREARRAY_HPP
