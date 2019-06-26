#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Material.h"
#include "Sprite.h"
#include "Player.h"
#include <iostream>
#include "Tilemap.h"
#include "World.h"

using namespace std;

class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	int loopCount;
	Square* square;
	Material* mat;
	Player* player;
	World* world;
	Tilemap* tilemap;
	float* coord;
	float conta;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

