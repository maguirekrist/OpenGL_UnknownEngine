//
//  main.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 4/16/22.
//
#include <array>
#include <GL/glew.h>
#include <iostream>
#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <algorithm>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Types.hpp"
#include "Cube.hpp"
#include "CubeRenderer.hpp"
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.h"
#include "World.h"
#include "WorldRenderer.h"
#include "QuadRenderer.h"

static Texture generateRandomTestTexture(int width, int height)
{
    srand(time(NULL));
    std::vector<std::uint8_t> stuff;
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            stuff.push_back((rand() % 255));
            stuff.push_back((rand() % 255));
            stuff.push_back((rand() % 255));
            stuff.push_back(0xff);
        }
    }
    Texture text;
    text.generate(width, height, stuff.data());
    return text;
}

int main(int argc, const char * argv[]) {
    // insert code here...s

    Camera camera(glm::vec3(0.0f, 0.0f, -1.0f));
    Window window(camera);

    //Load resources
    ResourceManager::loadShader("../shaders/colors.vert", "../shaders/colors.frag", nullptr, "cube");
    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/world.vert", "../shaders/world.frag", nullptr, "world");
    ResourceManager::loadShader("../shaders/simple.vert", "../shaders/simple.frag", nullptr, "simple");

    ResourceManager::loadTexture("../resources/tilemap_packed.png", true, "container");


    //Initialize renderers
    SpriteRenderer* spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    WorldRenderer* worldRenderer = new WorldRenderer(ResourceManager::getShader("world"));

    QuadRenderer* testRenderer = new QuadRenderer(ResourceManager::getShader("simple"));


    World world;

    world.generate(32, 32);

    Texture worldText = world.generateWorldTexture();

    std::cout << worldText.width << std::endl;

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    while(window.isOpen())
    {
        window.processInput();
        
        glClearColor(0.4f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        testRenderer->drawQuad(worldText, ResourceManager::getTexture("container"), camera, window);

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

