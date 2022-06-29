//
//  Shader.hpp
//  OpenGlBasic
//
//  Created by Maguire Krist on 6/2/22.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderProgram {
public:
    ShaderProgram(const char * vertexPath, const char * fragmentPath);
    ~ShaderProgram();
    
    void setMat4(const char * name, glm::mat4 mat4);
    void setVec3(const char * name, glm::vec3 vec3);
    void setVec4(const char * name, glm::vec4 vec4);
    void setInt(const char * name, int value);
    
    void use();
private:
    unsigned int shaderProgram;
    unsigned int compileVertexShader(const char *shaderSource);
    unsigned int compileFragmentShader(const char *shaderSource);
    
};


#endif /* Shader_hpp */
