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
#include <memory>
#include "Camera.hpp"
#include "Shader.hpp"
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "World.h"
#include "Renderers/QuadRenderer.h"
#include "renderers/FontRenderer.h"
#include "utils/Timer.h"
#include "NoiseGenerator.h"
#include "TextureArray.hpp"

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

enum DebugView {
    None,
    HeightMap
};

static Texture get_height_map_texture(std::vector<int>& map)
{
    std::vector<std::uint8_t> stuff;
    int mapSize = std::sqrt(map.size());
    for(int iter : map) {
        int value = std::clamp((iter / 16.0f) * 255, 0.0f, 255.0f);
        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(value);
        stuff.push_back(0xff);
    }

    Texture text;

    text.image_format = GL_RGBA;
    text.internal_format = GL_RGBA;

    text.generate(mapSize, mapSize, stuff.data());
    return text;
}


int main(int argc, const char * argv[]) {
    DebugView debugView = DebugView::None;

    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
    Window window(camera, WINDOW_WIDTH, WINDOW_HEIGHT);



    //Load resources
    //ResourceManager::loadShader("../shaders/colors.vert", "../shaders/colors.frag", nullptr, "cube");
    ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/world.vert", "../shaders/world.frag", nullptr, "world");
    ResourceManager::loadShader("../shaders/font.vert", "../shaders/font.frag", nullptr, "font");



    ResourceManager::loadTexture("../resources/jawbreaker_tiles.png", true, "tileset", std::nullopt);
    ResourceManager::loadTexture("../resources/ambient_gradient.png", true, "ambient", [](Texture& texture) {
        texture.dimension = GL_TEXTURE_1D;
        texture.mag_filter = GL_LINEAR;
    });

    ResourceManager::loadTexture("../resources/tiles/Soil.psd", true, "soil", std::nullopt);
    ResourceManager::loadTexture("../resources/tiles/SoftSand.psd", true, "sand", std::nullopt);

    TextureArray textureArray(GL_TEXTURE_2D_ARRAY);
    textureArray.insertTexture(&ResourceManager::getTexture("soil"));
    textureArray.insertTexture(&ResourceManager::getTexture("sand"));
    textureArray.generate();

    FontRenderer* fontRenderer = new FontRenderer(ResourceManager::getShader("font"));
    QuadRenderer* worldRenderer = new QuadRenderer(ResourceManager::getShader("world"));
    QuadRenderer* testRenderer = new QuadRenderer(ResourceManager::getShader("sprite"));

    fontRenderer->loadFont("../resources/fonts/arial.ttf");

    World world(256, 256,
                textureArray,
                ResourceManager::getTexture("ambient"),
                std::make_unique<NoiseGenerator>());

    world.generate(256, 256);

    world.addLight(Light(glm::ivec2(32, 32), 1.0f, 12));
    world.addLight(Light(glm::ivec2(64, 64), 1.0f, 12));

    auto lambda = [&](glm::ivec2 pos, bool isLight = false){
        std::cout << "Light added" << std::endl;
        if(isLight)
            world.addLight(Light(pos, 1.0f, 8));
        else
            world.placeTile(Tile(glm::ivec2(5, 4), pos, 8, 8, TileType::Terrain));
    };

    window.events.emplace_back(lambda);

    Texture testText = get_height_map_texture(world.heightMap);

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

        if(debugView == DebugView::None)
            worldRenderer->drawWorld(world, camera);
        if(debugView == DebugView::HeightMap)
            testRenderer->drawQuad(testText, camera);

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

