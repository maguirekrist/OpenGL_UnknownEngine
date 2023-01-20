//
// Created by magui on 9/14/2022.
//

#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(Shader& shader) {
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
            -1.0f, -1.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f,

            1.0f, 1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 0.0f, 1.0f,
            1.0f, -1.0f, 1.0f, 0.0f
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

void WorldRenderer::drawWorld(const World& world, const Camera& camera, DebugView& debugView) {
    this->shader.use();


    this->shader.setMat4("view", camera.view);
    this->shader.setInt("tileMap", 0);
    this->shader.setInt("atlas", 1);
    this->shader.setInt("lightMap", 2);
    this->shader.setInt("ambient", 3);
    this->shader.setFloat("worldTime", world.worldTime);
    this->shader.setInt("heightMapView", debugView == DebugView::HeightMap ? 1 : 0);
    this->shader.setVec3("selectTile", glm::vec3(camera.cursorPos, 1.0f));

    glActiveTexture(GL_TEXTURE0);
    world.tileMap.bind();

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D_ARRAY, world.atlas.ID);

    glActiveTexture(GL_TEXTURE2);
    world.lightMap.bind();

    glActiveTexture(GL_TEXTURE3);
    world.ambient.bind();
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    //glDisable(GL_BLEND);
}

void WorldRenderer::drawQuad(const Texture& texture, const Camera& camera) {
    this->shader.use();
    this->shader.setInt("aTexture", 0);
//    this->shader.setMat4("view", camera.view);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}