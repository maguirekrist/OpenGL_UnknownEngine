#pragma once
#include <glm/glm.hpp>

typedef struct
{
    float x, y, z;
    float nx, ny, nz;
    float u, v;
} Vertex;

typedef struct
{
    glm::vec3 min;
    glm::vec3 max;
} AABB;
