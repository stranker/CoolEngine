#pragma once
#include "Renderer.h"

class Entity
{
public:
	Entity(Renderer* _renderer);
	~Entity();		
	virtual void Draw() = 0;
protected:
	Renderer * renderer;	
};

