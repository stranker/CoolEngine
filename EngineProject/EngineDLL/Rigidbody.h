#pragma once
#include "Box2D/Box2D.h"

class Rigidbody
{
public:
	Rigidbody(b2BodyType _bodyType);
	~Rigidbody();
private:
	b2BodyType bodyType;
};

