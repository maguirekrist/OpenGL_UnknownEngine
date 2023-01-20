#pragma once

#include <glm/glm.hpp>

struct Light
{
	Light(glm::ivec2 position, float strength, int radius) : position(position), strength(strength), radius(radius) {};

    float strength;
    int radius;
	glm::ivec2 position;
};

