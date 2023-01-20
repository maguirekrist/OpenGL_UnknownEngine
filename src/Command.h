#pragma once
#include <glm/glm.hpp>

class Command
{
public:
	virtual ~Command() {} //what does a virtual destructor do again?
	virtual void execute(glm::vec2 pos) = 0;
};

