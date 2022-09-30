//
//  main.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 4/16/22.
//

#include <array>
#include <GL/glew.h>
#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "Renderers/SpriteRenderer.h"
#include "World.h"
#include "Renderers/WorldRenderer.h"
#include "Renderers/QuadRenderer.h"
#include "renderers/FontRenderer.h"
#include "utils/Timer.h"

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

int main(int argc, const char * argv[]) {
    // insert code here...s

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
    Window window(camera, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Load resources
    ResourceManager::loadShader("../shaders/colors.vert", "../shaders/colors.frag", nullptr, "cube");
    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/world.vert", "../shaders/world.frag", nullptr, "world");
    ResourceManager::loadShader("../shaders/simple.vert", "../shaders/simple.frag", nullptr, "simple");
    ResourceManager::loadShader("../shaders/font.vert", "../shaders/font.frag", nullptr, "font");


    ResourceManager::loadTexture("../resources/jawbreaker_tiles.png", true, "container", std::nullopt);
    ResourceManager::loadTexture("../resources/ambient_gradient.png", true, "ambient", [](Texture& texture) {
        texture.dimension = GL_TEXTURE_1D;
        texture.mag_filter = GL_LINEAR;
    });

    //Initialize renderers
//    SpriteRenderer* spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
//    WorldRenderer* worldRenderer = new WorldRenderer(ResourceManager::getShader("world"));

    FontRenderer* fontRenderer = new FontRenderer(ResourceManager::getShader("font"));
    QuadRenderer* testRenderer = new QuadRenderer(ResourceManager::getShader("simple"));

    fontRenderer->loadFont("../resources/fonts/arial.ttf");

    World world(256, 256, ResourceManager::getTexture("container"), ResourceManager::getTexture("ambient"));

    world.generate(256, 256);

    world.addLight(Light(glm::ivec2(32, 32), 1.0f, 12));
    world.addLight(Light(glm::ivec2(64, 64), 1.0f, 12));

//    Texture lightMap = world.generateWorldLightTexture();
//    Texture worldText = world.generateWorldTexture();

    auto lambda = [&](glm::ivec2 pos, bool isLight = false){
        std::cout << "Light added" << std::endl;

        world.addLight(Light(pos, 1.0f, 8));
    };

    window.events.emplace_back(lambda);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    double simulationAccum = 0;
    const double simulationTick = 1.0 / 60.0;
    double timeAccel = 8;

    Timer timer;

    while(window.isOpen())
    {
        double dt = timer.Elapsed_s(); // dt is the amount of time that has elapsed in seconds from the reset
        timer.Reset();
        simulationAccum += dt;
        while(simulationAccum > simulationTick)
        {
            window.processInput();

            camera.updateCamSpeed(simulationTick);
            camera.updateCamView();

            world.tickWorldTime(simulationTick);

            simulationAccum -= ( simulationTick / timeAccel);
        }
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        testRenderer->drawWorld(world, camera);

        std::ostringstream strs;
        strs << world.worldTime;
        fontRenderer->renderText(strs.str(), camera, glm::vec2(0.0f, 0.0f), 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        window.update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ResourceManager::clear();

    glfwTerminate();
    return 0;
}

