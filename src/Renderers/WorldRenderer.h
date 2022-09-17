//
// Created by magui on 9/12/2022.
//

#ifndef ALPHAENGINECMAKE_WORLDRENDERER_H
#define ALPHAENGINECMAKE_WORLDRENDERER_H


#include "Shader.hpp"
#include "World.h"
#include "Texture.hpp"
#include "Camera.hpp"

class WorldRenderer {
public:
    WorldRenderer(Shader &shader);
    ~WorldRenderer();

    void DrawWorld(World& world, Texture &atlas, Camera& camera);
private:
    Shader shader;
    unsigned int quadVAO;

    void initRenderData();
};


#endif //ALPHAENGINECMAKE_WORLDRENDERER_H
