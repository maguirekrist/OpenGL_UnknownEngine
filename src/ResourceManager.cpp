
#include "ResourceManager.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

std::map<std::string, Texture>    ResourceManager::textures;
std::map<std::string, Shader>       ResourceManager::shaders;

void ResourceManager::clear() {

    for(auto iter : shaders)
        glDeleteProgram(iter.second.ID);

    for(auto iter : shaders)
        glDeleteTextures(1, &iter.second.ID);

    shaders.clear();
    textures.clear();
}

Shader& ResourceManager::getShader(std::string name) {
    return shaders[name];
}

Texture& ResourceManager::getTexture(std::string name) {

    return textures[name];
}

void ResourceManager::loadShader(const char *vShaderFile,
                                          const char *fShaderFile,
                                          const char *gShaderFile,
                                          const std::string name) {
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;

    try {
        std::ifstream vertexShaderFile(vShaderFile);
        std::ifstream fragmentShaderFile(fShaderFile);

        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vertexShaderFile.rdbuf();
        fShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

        if(gShaderFile != nullptr)
        {
            std::ifstream geometryShaderFile(gShaderFile);
            std::stringstream gShaderStream;
            gShaderStream << geometryShaderFile.rdbuf();
            geometryShaderFile.close();
            geometryCode = gShaderStream.str();
        }

    } catch(std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SECESSFULLY_READ" << std::endl;
    }

    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();
    const char* gShaderCode = geometryCode.c_str();

    Shader shader;
    shader.compile(vShaderCode, fShaderCode, gShaderFile != nullptr ? gShaderCode : nullptr);

    shaders[name] = shader;
}

void ResourceManager::loadTexture(const char *file, bool alpha, std::string name, std::optional<std::function<void(Texture&)>> lambda) {
    Texture texture;

    if(lambda.has_value())
        lambda.value()(texture);

    if(alpha)
    {
        texture.internal_format = GL_RGBA;
        texture.image_format = GL_RGBA;
    }

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    if (data) {
        texture.generate(width, height, data);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    textures[name] = texture;

}