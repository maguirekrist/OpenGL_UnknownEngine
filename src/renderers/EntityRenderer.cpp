#include "EntityRenderer.h"


EntityRenderer::EntityRenderer(Shader& shader) {

}

EntityRenderer::~EntityRenderer() {
	glDeleteVertexArrays(1, &this->quadVAO);
}

void EntityRenderer::initRenderData() {
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
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void EntityRenderer::drawEntity(const Entity& entity, const Camera& camera) {
    this->shader.use();
    this->shader.setInt("aTexture", 0);
    //    this->shader.setMat4("view", camera.view);

    glActiveTexture(GL_TEXTURE0);
    //texture.bind();

    glBindVertexArray(this->quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

}
