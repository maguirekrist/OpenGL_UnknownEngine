//
// Created by magui on 9/14/2022.
//

#ifndef ALPHAENGINECMAKE_QUADRENDERER_H
#define ALPHAENGINECMAKE_QUADRENDERER_H


#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"
#include "World.h"

class QuadRenderer {
public:
    QuadRenderer(Shader& shader);
    ~QuadRenderer();

    unsigned int quadVAO;
    Shader shader;

    void initRenderData();

    void drawQuad(Texture& texture, Texture& atlas, Texture& lightMap, Camera& camera);
    void drawWorld(const World& world, const Camera& camera);
};


#endif //ALPHAENGINECMAKE_QUADRENDERER_H