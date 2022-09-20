#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>


class Texture
{
public:
	Texture();
	
	unsigned int ID;

    unsigned int internal_format; // format of texture object
    unsigned int image_format; // format of loaded image

    unsigned int min_filter;
    unsigned int mag_filter;

	int height;
	int width;
	int nrChannels;

    void generate(unsigned int width, unsigned int height, unsigned char* data);

	//const member function cannot change member variables without compile errors
	void bind() const;
};

