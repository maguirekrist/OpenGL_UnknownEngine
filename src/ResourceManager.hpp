#pragma once
#include <map>
#include "Texture.hpp"
#include "Shader.hpp"

class ResourceManager
{
public:

	static Shader& getShader(std::string name);
	static Texture& getTexture(std::string name);
	
	static void loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static void loadTexture(const char* file, bool alpha, std::string name);

    static void clear();
private:
    //Resource storage
	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;

	ResourceManager() {}

};

