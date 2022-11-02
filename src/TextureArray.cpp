//
// Created by Maguire Krist on 11/1/22.
//

#include "TextureArray.hpp"


void TextureArray::generate() {

    this->bind();

    this->height = textures[0]->height;
    this->width = textures[0]->width;

    glTexParameteri(dimension, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(dimension, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, this->min_filter);
    glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, this->mag_filter);

    std::vector<std::byte> texels;
    //texels.reserve(width * height * textures.size());

    int imageOffset = (width * height * (image_format == GL_RGBA ? 4 : 3));

    for(auto& text : textures)
    {
        texels.insert(texels.end(), text->data.data(), text->data.data() + imageOffset);
    }
    //allocate storage
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, width, height, textures.size());

    //Upload texel data
    glTexSubImage3D(dimension, 0, 0, 0, 0, width, height, textures.size(), GL_RGBA, GL_UNSIGNED_BYTE, texels.data());

    glBindTexture(dimension, 0);
}

void TextureArray::insertTexture(Texture *text) {
    textures.emplace_back(text);
}