#pragma once
#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
<<<<<<< HEAD
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
=======
	Renderer* renderer;
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
public:
	Entity(Renderer* _renderer);
	~Entity();		
	virtual void Draw() = 0;
};

