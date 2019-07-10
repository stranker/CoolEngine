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
	float* coord;
	float conta;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

