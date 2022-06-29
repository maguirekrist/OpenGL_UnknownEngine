#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <iostream>


class Texture
{
public:
	Texture(const char * path);
	~Texture();
	
	unsigned int ID;

	int height;
	int width;
	int nrChannels;

	//const member function cannot change member variables without compile errors
	void Bind() const;
};

