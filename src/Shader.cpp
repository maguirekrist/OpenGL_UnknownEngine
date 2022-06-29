//
//  Shader.cpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/2/22.
//

#include "Shader.hpp"


ShaderProgram::ShaderProgram(const char * vertexPath, const char * fragmentPath) {

    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try {
        vertexShaderFile.open(vertexPath);
        fragmentShaderFile.open(fragmentPath);
        std::ostringstream vShaderStream, fShaderStream;
        
        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();
        
        vertexShaderFile.close();
        fragmentShaderFile.close();
        
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        
    } catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SECESSFULLY_READ" << std::endl;
    }
    
    unsigned int vertexShader = compileVertexShader(vertexCode.c_str());
    unsigned int fragmentShader = compileFragmentShader(fragmentCode.c_str());
    
    //Create Shader Program
    shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
   
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(shaderProgram);
}

void ShaderProgram::setMat4(const char* name, glm::mat4 mat4) {
    unsigned int mat4Loc = glGetUniformLocation(shaderProgram, name);
    glUniformMatrix4fv(mat4Loc, 1, GL_FALSE, glm::value_ptr(mat4));
}

void ShaderProgram::setVec3(const char * name, glm::vec3 vec3) {
    unsigned int vec3Loc = glGetUniformLocation(shaderProgram, name);
    glUniform3fv(vec3Loc, 1, glm::value_ptr(vec3));
}

void ShaderProgram::setVec4(const char * name, glm::vec4 vec4) {
    unsigned int vec4Loc = glGetUniformLocation(shaderProgram, name);
    glUniform4fv(vec4Loc, 1, glm::value_ptr(vec4));
}

void ShaderProgram::setInt(const char * name, int value) {
    unsigned int loc = glGetUniformLocation(shaderProgram, name);
    glUniform1i(loc, value);
}

void ShaderProgram::use() {
    glUseProgram(shaderProgram);
}

unsigned int ShaderProgram::compileVertexShader(const char *shaderSource)
{
    unsigned int vertexShader;
    int success;
    char infoLog[512];
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &shaderSource, NULL);
    glCompileShader(vertexShader);
    
    std::cout << &vertexShader << std::endl;
    
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER:VERTEX_COMPLIATION::FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return vertexShader;
}

unsigned int ShaderProgram::compileFragmentShader(const char *shaderSource)
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
