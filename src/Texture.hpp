#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>
#include <vector>


class  Texture
{
protected:
    Texture(int dimension) :  internal_format(GL_RGBA), image_format(GL_RGBA), min_filter(GL_LINEAR), mag_filter(GL_NEAREST), dimension(dimension), nrChannels(4) {
        glGenTextures(1, &this->ID);
    }
public:
	Texture();
	
	unsigned int ID;

    unsigned int internal_format; // format of texture object
    unsigned int image_format; // format of loaded image

    unsigned int min_filter;
    unsigned int mag_filter;

    unsigned int dimension;

	int height;
	int width;
	int nrChannels;

    std::vector<std::uint8_t> data;

    //Make virtual so composite objects can utilize this
    void generate(unsigned int width, unsigned int height, unsigned char* data);

	//const member function cannot change member variables without compile errors
	void bind() const;
};

