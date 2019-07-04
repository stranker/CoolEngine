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
#include "Platform.h"

using namespace std;

class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	int loopCount;
	Material* mat;
	Player* player;
	Platform* landingPlatform;
	b2World* world2D;
	Tilemap* tilemap;
	float* coord;
	float conta;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

