#pragma once
#include <map>
#include "Texture.hpp"
#include "Shader.hpp"

class ResourceManager
{
public:
	static ShaderProgram& getShader(std::string name);
	static Texture& getTexture(std::string name);
	
	static void storeShader(ShaderProgram& shader, std::string name);
	static void storeTexture(Texture& texture, std::string name);

private:
	static std::map<std::string, Texture> textures;
	static std::map<std::string, ShaderProgram> shaders;

	ResourceManager() {}

};

