#include "World.h"

World::World(b2Vec2 _gravity, bool _sleep)
{
	gravity = _gravity;
	doSleep = _sleep;
	myWorld = new b2World(gravity);
}

World::World()
{
	gravity = b2Vec2(0,-9.8);
	doSleep = true;
	myWorld = new b2World(gravity);
}

World::~World()
{
	delete myWorld;
}
