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

const int WINDOW_HEIGHT = 1024;
const int WINDOW_WIDTH = 1024;

int main(int argc, const char * argv[]) {
    // insert code here...s

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
    Window window(camera, WINDOW_WIDTH, WINDOW_HEIGHT);

    //Load resources
    ResourceManager::loadShader("../shaders/colors.vert", "../shaders/colors.frag", nullptr, "cube");
    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/world.vert", "../shaders/world.frag", nullptr, "world");
    ResourceManager::loadShader("../shaders/simple.vert", "../shaders/simple.frag", nullptr, "simple");

    ResourceManager::loadTexture("../resources/tilemap_packed.png", true, "container");


    //Initialize Renderers
    SpriteRenderer* spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    WorldRenderer* worldRenderer = new WorldRenderer(ResourceManager::getShader("world"));

    QuadRenderer* testRenderer = new QuadRenderer(ResourceManager::getShader("simple"));


    World world;

    world.generate(256, 256);

    std::vector<Light> lights = {
            Light(glm::vec2(32, 32), 24.0f, 24.0f),
            Light(glm::vec2(32, 64), 24.0f, 24.0f)
    };

    Texture lightMap = world.generateWorldLightTexture(lights);
    Texture worldText = world.generateWorldTexture();

    auto lambda = [&](glm::vec2 pos){
        std::cout << "Light added" << std::endl;
        lights.push_back(Light(pos, 24.0f, 24.0f));
        lightMap = world.generateWorldLightTexture(lights);
    };

    window.events.push_back(lambda);


    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while(window.isOpen())
    {
        window.processInput();
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        testRenderer->drawQuad(worldText, ResourceManager::getTexture("container"), lightMap, camera);

        window.update();

        float currentFrame = glfwGetTime();
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        camera.updateCamSpeed(deltaTime);
        camera.updateCamView();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ResourceManager::clear();

    glfwTerminate();
    return 0;
}

