//
// Created by magui on 9/23/2022.
//

#ifndef WORLD_CPP_FONTRENDERER_H
#define WORLD_CPP_FONTRENDERER_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glm/ext/vector_int2.hpp>
#include <map>
#include "../graphics/Shader.h"
#include "../scene/Camera.h"

struct Character {
    unsigned int TextureID;
    glm::ivec2 Size;
    glm::ivec2 Bearing;
    unsigned int Advance;
};

class FontRenderer {
public:
    FontRenderer(Shader& shader);

    unsigned int quadVAO;
    unsigned int VBO;
    Shader shader;

    void initRenderData();

    void loadFont(const char* fontPath);
    void renderText(std::string text, Camera& camera, glm::vec2 position, float scale, glm::vec3 color);
private:
    std::map<char, Character> Characters;
    FT_Library ft;
    FT_Face face;
};


#endif //WORLD_CPP_FONTRENDERER_H
