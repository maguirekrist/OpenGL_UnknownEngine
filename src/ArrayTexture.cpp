//
// Created by Maguire Krist on 11/1/22.
//

#include "ArrayTexture.hpp"


void ArrayTexture::generate() {

    glBindTexture(GL_TEXTURE_2D_ARRAY,this->ID);

    this->dimension = GL_TEXTURE_2D_ARRAY;
    this->height = textures[0]->height;
    this->width = textures[0]->width;
    this->image_format = textures[0]->image_format;
    this->internal_format = textures[0]->internal_format;
    this->nrChannels = textures[0]->nrChannels;
    GLsizei mipLevelCount = 1;

    std::vector<std::uint8_t> texels;
    //texels.reserve(width * height * textures.size());

    int imageOffset = (width * height * nrChannels);

    for(auto& text : textures)
    {
        texels.insert(texels.end(), text->data.data(), text->data.data() + imageOffset);
    }

    //allocate storage
    glTexStorage3D(GL_TEXTURE_2D_ARRAY, mipLevelCount, GL_RGBA8, width, height, textures.size());

    //Upload texel dataFgl
    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, width, height, textures.size(), internal_format, GL_UNSIGNED_BYTE, texels.data());


    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);

    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
}

void ArrayTexture::insertTexture(Texture* text) {
    textures.emplace_back(text);
}