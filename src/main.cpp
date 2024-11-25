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
#include <format>
#include "scene/Camera.h"
#include "graphics/Shader.h"
#include "scene/Window.h"
#include "infrastructure/ResourceManager.h"
#include "scene/World.h"
#include "renderers/FontRenderer.h"
#include "utils/Timer.h"
#include "generation/NoiseGenerator.h"
#include "graphics/ArrayTexture.h"
#include "renderers/WorldRenderer.h"
#include "renderers/EntityRenderer.h"

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 800;

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

static std::optional<Tile> get_selected_tile(const Camera& camera, const World& world) {
    if (camera.cursorPos.x >= 0 && camera.cursorPos.x < world.width && camera.cursorPos.y >= 0 && camera.cursorPos.y < world.height)
        return world.tiles[(world.width * camera.cursorPos.y) + camera.cursorPos.x];
    else
        return std::nullopt;
}


int main(int argc, const char * argv[]) {
    Camera camera(glm::vec3(0.0f, 0.0f, 0.0f), WINDOW_WIDTH, WINDOW_HEIGHT);
    Window window(camera, WINDOW_WIDTH, WINDOW_HEIGHT);

    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    //Load resources
    //ResourceManager::loadShader("../shaders/colors.vert", "../shaders/colors.frag", nullptr, "cube");
    //ResourceManager::loadShader("../shaders/sprite.vert", "../shaders/sprite.frag", nullptr, "sprite");
    ResourceManager::loadShader("../shaders/world.vert", "../shaders/world.frag", nullptr, "world");
    ResourceManager::loadShader("../shaders/font.vert", "../shaders/font.frag", nullptr, "font");


    ResourceManager::loadTexture("../resources/jawbreaker_tiles.png", true, "tileset", std::nullopt);
    ResourceManager::loadTexture("../resources/ambient_gradient.png", true, "ambient", [](Texture& texture) {
        texture.dimension = GL_TEXTURE_1D;
        texture.mag_filter = GL_LINEAR;
    });

    FontRenderer* fontRenderer = new FontRenderer(ResourceManager::getShader("font"));
    WorldRenderer* worldRenderer = new WorldRenderer(ResourceManager::getShader("world"));
    EntityRenderer* entityRenderer = new EntityRenderer(ResourceManager::getShader("sprite"));
    
    fontRenderer->loadFont("../resources/fonts/arial.ttf");

    World world(512, 512,
                16,
                ResourceManager::getTexture("ambient"),
                std::make_unique<NoiseGenerator>());

    //world.addLight(Light(glm::ivec2(32, 32), 1.0f, 12));
    //world.addLight(Light(glm::ivec2(64, 64), 1.0f, 12));

    Texture testText = get_height_map_texture(world.heightMap);

    //std::unique_ptr<Command> placeCommand = std::make_unique<Command>(TileType::Water, world);

    //window.setPlaceCommand(std::move(placeCommand));

    std::vector<Entity> entities;
    
    entities.push_back(Entity(glm::vec2(5.0f, 5.0f)));


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

        if(window.debugView != DebugView::HeightMapTexture)
            worldRenderer->drawWorld(world, camera, window.debugView);



        std::ostringstream strs;
        strs << world.worldTime;
        std::optional<Tile> tileOpt = get_selected_tile(camera, world);
        fontRenderer->renderText(std::format("{}", tileOpt.has_value() ? (int)tileOpt.value().position.z : 0), camera, glm::vec2(0.0f, 0.0f), 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
        window.update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    ResourceManager::clear();
    glfwTerminate();
    return 0;
}

