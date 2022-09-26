//
//  Shader.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/2/22.
//

#include "Shader.hpp"

void Shader::compile(const char *vertexSource, const char *fragmentSource, const char *geometrySource) {
    unsigned int vertexShader = compileVertexShader(vertexSource);
    unsigned int fragmentShader = compileFragmentShader(fragmentSource);

    //Create Shader Program
    this->ID = glCreateProgram();

    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);

    //delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::setMat4(const char* name, glm::mat4 mat4) {
    unsigned int mat4Loc = glGetUniformLocation(this->ID, name);
    glUniformMatrix4fv(mat4Loc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void Shader::setVec2(const char * name, glm::vec2 vec2)
{
    unsigned int vec2Loc = glGetUniformLocation(this->ID, name);
    glUniform2fv(vec2Loc, 1, glm::value_ptr(vec2));
}

void Shader::setVec3(const char * name, glm::vec3 vec3) {
    unsigned int vec3Loc = glGetUniformLocation(this->ID, name);
    glUniform3fv(vec3Loc, 1, glm::value_ptr(vec3));
}

void Shader::setVec4(const char * name, glm::vec4 vec4) {
    unsigned int vec4Loc = glGetUniformLocation(this->ID, name);
    glUniform4fv(vec4Loc, 1, glm::value_ptr(vec4));
}

void Shader::setInt(const char * name, int value) {
    unsigned int loc = glGetUniformLocation(this->ID, name);
    glUniform1i(loc, value);
}

void Shader::setFloat(const char* name, float value) {
    unsigned int loc = glGetUniformLocation(this->ID, name);
    glUniform1f(loc, value);
}

Shader& Shader::use() {
    glUseProgram(this->ID);
    return *this;
}

unsigned int Shader::compileVertexShader(const char *shaderSource)
{
    unsigned int vertexShader;
    int success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:VERTEX_COMPLIATION::FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return vertexShader;
}

unsigned int Shader::compileFragmentShader(const char *shaderSource)
{
    unsigned int fragmentShader;
    int success;
    char infoLog[512];
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &shaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:FRAGMENT::FAILED\n" << infoLog << std::endl;
        return 0;
    }

    return fragmentShader;
}