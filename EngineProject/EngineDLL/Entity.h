#pragma once
#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scl;

	glm::mat4 model;
	glm::mat4 translate;
	glm::mat4 rotateX;
	glm::mat4 rotateY;
	glm::mat4 rotateZ;
	glm::mat4 scale;

	Renderer* renderer;	
public:
	Entity(Renderer* _renderer);
	~Entity();		
	virtual void Draw() = 0;
};

