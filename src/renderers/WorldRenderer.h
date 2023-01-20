//
// Created by magui on 9/14/2022.
//

#pragma once

#include "../graphics/Shader.h"
#include "../graphics/Texture.h"
#include "../scene/World.h"
#include "../scene/Camera.h"
#include "../scene/Window.h"


class WorldRenderer {
public:
    WorldRenderer(Shader& shader);
    ~WorldRenderer();

    unsigned int quadVAO;
    Shader shader;

    void initRenderData();

    void drawQuad(const Texture& texture, const Camera& camera);
    void drawWorld(const World& world, const Camera& camera, DebugView& debugView);
};



