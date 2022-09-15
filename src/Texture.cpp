#include <array>
#include <cstring>
#include <vector>
#include "Texture.hpp"

#define ASSERT(x) if (!(x)) __debugbreak();
#define GLCall(x) glClearError(); \
    x;                            \
    ASSERT(glLogCall())
static void glClearError()
{
    while(glGetError() != GL_NO_ERROR);
}

static bool glLogCall()
{
    while(GLenum error = glGetError())
    {
        std::cout << "[OpenGL ERROR]: " << error << std::endl;
        return false;
    }
    return true;
}

Texture::Texture() : internal_format(GL_RGB), image_format(GL_RGB)
{
    glGenTextures(1, &this->ID);
}

void Texture::generate(unsigned int width, unsigned int height, unsigned char *data) {
    this->width = width;
    this->height = height;

    glBindTexture(GL_TEXTURE_2D, this->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); //GL_NEAREST is good for pixel graphics

    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, this->internal_format, width, height, 0, this->image_format, GL_UNSIGNED_BYTE, data));

    glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->ID);
}
