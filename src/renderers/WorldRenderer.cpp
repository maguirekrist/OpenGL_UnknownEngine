//
// Created by magui on 9/12/2022.
//

#include "WorldRenderer.h"
WorldRenderer::WorldRenderer(Shader &shader) {
    this->shader = shader;
    this->initRenderData();
}

WorldRenderer::~WorldRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void WorldRenderer::initRenderData() {
    unsigned int VBO;
    float vertices[] = {
            // pos      // tex
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *) 0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void WorldRenderer::DrawWorld(World &world, Texture &atlas, Camera &camera) {
//    this->shader.use();
//
//    glm::mat4 model = glm::mat4(1.0f);
////    model = glm::translate(model, glm::vec3(0.5f * world.width, 0.5f * world.height, 0.0f));
////    model = glm::translate(model, glm::vec3(-0.5f * world.width, -0.5f * world.height, 0.0f));
//
//    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//
//    this->shader.setInt("atlasTexture", 0);
//    this->shader.setInt("tileMap", 1);
//    this->shader.setMat4("model", model);
//    this->shader.setMat4("view", camera.view);
//    this->shader.setMat4("projection", camera.projection);
//
//
//    glActiveTexture(GL_TEXTURE0);
//    atlas.bind();
//
//    glActiveTexture(GL_TEXTURE1);
//    tileMap.bind();
//
//
//    glBindVertexArray(this->quadVAO);
//    glDrawArrays(GL_TRIANGLES, 0, 6);
//    glBindVertexArray(0);
}