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


int main(int argc, const char * argv[]) {
    // insert code here...

    Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
    Window window(camera);


    //SETUP Vertex Shader
    ShaderProgram objectsShader("../shaders/colors.vert", "../shaders/colors.frag");
    ShaderProgram lightingShader("../shaders/light_source.vert", "../shaders/light_source.frag");
    
    Texture cubeTexture("../resources/container.jpg");

    CubeRenderer cubeRenderer;
    
    std::vector<Cube> cubeObjects = {
        Cube(glm::vec3(2.0f,  5.0f, -15.0f), cubeTexture),
        Cube(glm::vec3(-1.5f, -2.2f, -2.5f), cubeTexture),
        Cube(glm::vec3(-3.8f, -2.0f, -12.3f), cubeTexture),
        Cube(glm::vec3(2.4f, -0.4f, -3.5f), cubeTexture),
        Cube(glm::vec3(-1.7f,  3.0f, -7.5f), cubeTexture),
        Cube(glm::vec3(1.3f, -2.0f, -2.5f), cubeTexture),
        Cube(glm::vec3(1.5f,  2.0f, -2.5f), cubeTexture),
        Cube(glm::vec3(1.5f,  0.2f, -1.5f), cubeTexture),
        Cube(glm::vec3(-1.3f,  1.0f, -1.5f), cubeTexture)
    };

    window.loadSceneItems(cubeObjects);

    unsigned int lightCubeVAO, lightCubeVBO;

    glGenVertexArrays(1, &lightCubeVAO);
    glGenBuffers(1, &lightCubeVBO);

    glBindVertexArray(lightCubeVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, lightCubeVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);
    
    //Draw wire frames when uncommented
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  
    
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    
    while(window.isOpen())
    {
        window.processInput();
        
        
        glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
        
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       
        
        objectsShader.use();
        objectsShader.setVec4("lightSource", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        objectsShader.setVec3("lightPos", lightPos);
        objectsShader.setVec3("viewPos", camera.cameraPos);


        for(unsigned int i = 0; i < 8; i++)
        {   
           
            cubeRenderer.Render(cubeObjects[i], objectsShader, camera);
        }
        
        //
        //lightingShader.use();
        //lightingShader.setMat4("view", camera.view);
        //lightingShader.setMat4("projection", camera.projection);
        //glm::mat4 model = glm::mat4(1.0f);
        //model = glm::translate(model, lightPos);
        //model = glm::scale(model, glm::vec3(0.2f));
        //lightingShader.setMat4("model", model);
        //
        //glBindVertexArray(lightCubeVAO);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //
       
        window.update();

        float currentFrame = glfwGetTime();
        
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        
        camera.updateCamSpeed(deltaTime);
        camera.updateCamView();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    glfwTerminate();
    return 0;
}

