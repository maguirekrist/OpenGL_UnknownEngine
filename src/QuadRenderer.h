//
// Created by magui on 9/14/2022.
//

#ifndef ALPHAENGINECMAKE_QUADRENDERER_H
#define ALPHAENGINECMAKE_QUADRENDERER_H


#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Window.hpp"

class QuadRenderer {
public:
    QuadRenderer(Shader& shader);
    ~QuadRenderer();

    unsigned int quadVAO;
    Shader shader;

    void initRenderData();

    void drawQuad(Texture& texture, Texture& atlas, Camera& camera, Window& window);
};


#endif //ALPHAENGINECMAKE_QUADRENDERER_H
