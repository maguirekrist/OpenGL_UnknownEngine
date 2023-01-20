#pragma once
#include "../graphics/Shader.h"
#include "../scene/Entity.h"
#include "../scene/Person.h"
#include "../scene/Camera.h"


class EntityRenderer
{
public:
	EntityRenderer(Shader& shader);
	~EntityRenderer();

	void drawEntity(const Entity& entity, const Camera& camera);
	void drawPerson(const Person& person, const Camera& camera);

private:

	unsigned int quadVAO;
	Shader shader;

	void initRenderData();
};

