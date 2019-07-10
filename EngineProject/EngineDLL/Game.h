#pragma once
#include <iostream>
#include "GameBase.h"
#include "CollisionManager.h"
#include "Material.h"
#include "Sprite.h"
#include "Player.h"
#include "Platform.h"
#include "Line2D.h"
#include "Turret.h"
#include "Bullet.h"

#define LENGTH_TERRAIN 100

using namespace std;

class Game : public GameBase
{
protected:
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate(float deltaTime) override;
	void CreateGameObjects();
	void CreateRigidbodies();
	int loopCount;
	Material* mat;
	Player* player;
	Platform* landingPlatform;
	b2World* world2D;
	Line2D* ground;
	Turret* turret;
	Turret* turret2;
	Bullet* bullet;
	float* coord;
	float conta;
	bool win = false;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

