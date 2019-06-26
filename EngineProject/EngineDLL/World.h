#pragma once
#include "Box2D\Box2D.h"

class World
{
public:
	World(b2Vec2 _gravity, bool _sleep);
	World();
	~World();
	b2Vec2 gravity;
	b2World* myWorld;
	bool doSleep = true;
};

