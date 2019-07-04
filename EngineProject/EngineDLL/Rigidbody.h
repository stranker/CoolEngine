#pragma once
#include "Box2D/Box2D.h"

class Rigidbody
{
public:
	Rigidbody(b2BodyType _bodyType, b2Vec2 _initalPos);
	~Rigidbody();
private:
	b2BodyDef bodyDef;
	b2Vec2 pos;
};

