#pragma once
#include "Renderer.h"

class ENGINEDLL_API Entity
{
protected:
	Renderer* renderer;
public:
	Entity(Renderer* _renderer);
	~Entity();		
	virtual void Draw() = 0;
};

