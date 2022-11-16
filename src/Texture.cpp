#include <array>
#include <cstring>
#include <vector>
#include "Texture.hpp"

//static void glClearError()
//{
//    while(glGetError() != GL_NO_ERROR);
//}
//
//static bool glLogCall()
//{
//    while(GLenum error = glGetError())
//    {
//        std::cout << "[OpenGL ERROR]: " << error << std::endl;
//        return false;
//    }
//    return true;
//}

Texture::Texture() : internal_format(GL_RGB), image_format(GL_RGB), min_filter(GL_LINEAR), mag_filter(GL_NEAREST), dimension(GL_TEXTURE_2D), nrChannels(3)
{
    glGenTextures(1, &this->ID);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char* data) {
    this->width = width;
    this->height = height;

    this->data.resize(width * height * nrChannels);
    memcpy(this->data.data(), data, width * height * nrChannels);

    glBindTexture(dimension, this->ID);

    glTexParameteri(dimension, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(dimension, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(dimension, GL_TEXTURE_MIN_FILTER, this->min_filter);
    glTexParameteri(dimension, GL_TEXTURE_MAG_FILTER, this->mag_filter); //GL_NEAREST is good for pixel graphics

    switch(dimension) {
        case GL_TEXTURE_2D:
            glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data);
            break;
        case GL_TEXTURE_1D:
            glTexImage1D(GL_TEXTURE_1D, 0, this->internal_format, width, 0, this->image_format, GL_UNSIGNED_BYTE, data);
            break;
    }

    glBindTexture(dimension, 0);
}

void Texture::bind() const
{
    glBindTexture(dimension, this->ID);
}
