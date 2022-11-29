#ifndef RESOURCE_MANAGER_HPP
#define RESOURCE_MANAGER_HPP

#include <map>
#include <functional>
#include <optional>
#include <string>
#include "../graphics/Texture.h"
#include "../graphics/Shader.h"


class ResourceManager
{
public:

	static Shader& getShader(std::string name);
	static Texture& getTexture(std::string name);
	
	static void loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);
	static void loadTexture(const char* file, bool alpha, std::string name, std::optional<std::function<void(Texture&)>> = std::nullopt);

    static void clear();
private:
    //Resource storage
	static std::map<std::string, Texture> textures;
	static std::map<std::string, Shader> shaders;

	ResourceManager() {}

    void loadTexture(const char *file, bool alpha, std::string name);
};

#endif