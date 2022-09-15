//
// Created by magui on 9/10/2022.
//

#include "SpriteRenderer.h"
#include "Camera.hpp"

SpriteRenderer::SpriteRenderer(Shader &shader) {
    this->shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer() {
    glDeleteVertexArrays(1, &this->quadVAO);
}

void SpriteRenderer::initRenderData() {
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

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec3 position, Camera& camera, glm::vec2 size, float rotate, glm::vec3 color) {
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);

    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));


    this->shader.setInt("aTexture", 0);
    this->shader.setVec3("spriteColor", color);
    this->shader.setMat4("model", model);
    this->shader.setMat4("view", camera.view);
    this->shader.setMat4("projection", camera.projection);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::DrawTile(Tile &tile, Texture &atlas, Camera &camera) {
    this->shader.use();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(tile.position, 0.0f));

    model = glm::scale(model, glm::vec3(glm::vec2(1.0f, 1.0f), 1.0f));

    this->shader.setVec2("tileCoord", glm::vec2(tile.offsetX, tile.offsetY));
    this->shader.setVec3("spriteColor", glm::vec3(1.0f));
    this->shader.setMat4("model", model);
    this->shader.setMat4("view", camera.view);
    this->shader.setMat4("projection", camera.projection);

    glActiveTexture(GL_TEXTURE0);
    atlas.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


