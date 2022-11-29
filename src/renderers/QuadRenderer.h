//
// Created by magui on 9/14/2022.
//

#ifndef ALPHAENGINECMAKE_QUADRENDERER_H
#define ALPHAENGINECMAKE_QUADRENDERER_H


#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../scene/World.h"
#include "../scene/Camera.h"
#include "../scene/Window.h"


class QuadRenderer {
public:
    QuadRenderer(Shader& shader);
    ~QuadRenderer();

    unsigned int quadVAO;
    Shader shader;

    void initRenderData();

    void drawQuad(const Texture& texture, const Camera& camera);
    void drawWorld(const World& world, const Camera& camera, DebugView& debugView);
};


#endif //ALPHAENGINECMAKE_QUADRENDERER_H
