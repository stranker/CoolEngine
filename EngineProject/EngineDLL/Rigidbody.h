#pragma once
#include "Box2D/Box2D.h"

class Rigidbody
{
public:
	Rigidbody(b2BodyType _bodyType);
	~Rigidbody();
private:
	b2BodyDef bodyDef;
	b2Body* body;
	b2FixtureDef fixtureDef;
};

