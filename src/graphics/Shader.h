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
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
    unsigned int ID;
    Shader() {}
    
    void setMat4(const char * name, glm::mat4 mat4);
    void setVec2(const char * name, glm::vec2 vec2);
    void setVec3(const char * name, glm::vec3 vec3);
    void setVec4(const char * name, glm::vec4 vec4);
    void setInt(const char * name, int value);
    void setFloat(const char * name, float value);
    void setBool(const char * name, bool value);

    void compile(const char* vertexSource, const char* fragmentSource, const char* geometrySource = nullptr);
    void compile(const char* computeSource);

    Shader& use();
private:
    unsigned int compileVertexShader(const char* vertexSource);
    unsigned int compileFragmentShader(const char* fragmentSource);
    unsigned int compileComputeShader(const char* computeSource);
};


#endif /* Shader_hpp */
