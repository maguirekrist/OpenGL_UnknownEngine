#pragma once
#include <glm/ext/vector_float2.hpp>



class Entity
{
public:

	Entity(glm::vec2 pos) : _position(pos) {};
	~Entity() {};

	glm::vec2 getPosition();
	glm::vec2 getVelocity();
	

private:
	glm::vec2 _position;
	glm::vec2 _veloctiy;
};

