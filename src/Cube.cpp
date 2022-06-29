#include "Cube.hpp"

Cube::Cube(glm::vec3 position, Texture& texture) : texture(texture)
{
    this->position = position;
    this->model = glm::translate(glm::mat4(1.0f), position);
    this->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
    glm::vec4 boxMin(-0.5f, -0.5f, -0.5f, 1.0f);
    glm::vec4 boxMax(0.5f, 0.5f, 0.5f, 1.0f);

    boxMin = model * boxMin;
    boxMax = model * boxMax;
    this->bounds = AABB{ glm::vec3(boxMin.x, boxMin.y, boxMin.z), glm::vec3(boxMax.x, boxMax.y, boxMax.z) };
}