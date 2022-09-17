#include "CubeRenderer.hpp"

CubeRenderer::CubeRenderer(Shader &shader)
{
    this->shader = shader;

    unsigned int VBO;

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices.front(), GL_STATIC_DRAW);

    glBindVertexArray(this->VAO);

    //
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

CubeRenderer::~CubeRenderer()
{
    glDeleteVertexArrays(1, &VAO);
}


void CubeRenderer::Render(Cube& cube, Camera& camera)
{
    this->shader.use();
    this->shader.setInt("aTexture", 0);
    this->shader.setVec4("aColor", cube.color);
    this->shader.setMat4("model", cube.model);
    this->shader.setMat4("view", camera.view);
    this->shader.setMat4("projection", camera.projection);

    glActiveTexture(GL_TEXTURE0);
    cube.texture.bind();

    glBindVertexArray(this->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}