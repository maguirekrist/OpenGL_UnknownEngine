#pragma once
#include "Types.hpp"
#include <stdlib.h>
#include <array>
#include <vector>
#include "Shader.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include <glm/gtc/matrix_transform.hpp>

class Cube {
public:
    Cube(glm::vec3 position, Texture& texture);

    glm::vec3 position;
    glm::mat4 model;
    AABB bounds;
    const Texture& texture;
    glm::vec4 color;

private:

};