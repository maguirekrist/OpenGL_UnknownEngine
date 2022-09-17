//
// Created by magui on 9/10/2022.
//

#ifndef ALPHAENGINECMAKE_SPRITERENDERER_H
#define ALPHAENGINECMAKE_SPRITERENDERER_H


#include <glm/glm.hpp>
#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Tile.h"
#include "World.h"

class SpriteRenderer {
public:
    SpriteRenderer(Shader &shader);
    ~SpriteRenderer();

    void DrawSprite(Texture &texture, glm::vec3 position, Camera& camera, glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                    glm::vec3 color = glm::vec3(1.0f));
    void DrawTile(Tile &tile, Texture &atlas, Camera& camera);

private:
    Shader shader;
    unsigned int quadVAO;

    void initRenderData();
};


#endif //ALPHAENGINECMAKE_SPRITERENDERER_H
