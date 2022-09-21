#pragma once

#include <glm/glm.hpp>

struct Light
{
	Light(glm::vec2 position, float strength, float radius) : position(position), strength(strength), radius(radius) {};

    float strength;
    float radius;
	glm::vec2 position;

};

