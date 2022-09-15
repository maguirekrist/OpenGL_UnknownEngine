//
// Created by magui on 9/14/2022.
//

#include "QuadRenderer.h"
#include "Window.hpp"

QuadRenderer::QuadRenderer(Shader& shader) {
    this->shader = shader;
    this->initRenderData();
}

QuadRenderer::~QuadRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void QuadRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[] = {
            // pos      // tex
            -1.0f, -1.0f,  //Bottom Left
            -1.0f, 1.0f,  //Top Left
            1.0f, -1.0f,  //Bottom Right

            1.0f, 1.0f,  //Top Right
            -1.0f, 1.0f,   //Top Left
            1.0f, -1.0f,  //Bottom right
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void QuadRenderer::drawQuad(Texture &texture, Texture& atlas, Camera& camera, Window& window) {
    this->shader.use();


    glm::mat4 world = glm::mat4(1.0f);
    world = glm::translate(world, camera.cameraPos);
    world = glm::scale(world, glm::vec3(camera.zoom, camera.zoom, 1.0f));


    this->shader.setMat4("view", world);
    this->shader.setInt("aTexture", 0);
    this->shader.setInt("atlas", 1);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glActiveTexture(GL_TEXTURE1);
    atlas.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}