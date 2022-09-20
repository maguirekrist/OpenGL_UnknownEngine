#pragma once

#include <glm/glm.hpp>

class Light
{
public:
	Light(glm::vec2 position, float strength, float radius) : position(position), strength(strength), radius(radius) {};


    bool active = true;
    float strength;
    float radius;
	glm::vec2 position;
private:

};

