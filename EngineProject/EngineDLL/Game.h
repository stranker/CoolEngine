#pragma once
#include "GameBase.h"
#include "CollisionManager.h"
#include "Triangle.h"
#include "Square.h"
#include "Circle.h"
#include "Material.h"
#include "Sprite.h"
#include <iostream>
using namespace std;
class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	int loopCount;
	Square* triangle;
	Circle* circle;
	Material* mat;
	Sprite* sprite;
	float* coord;
	float x;	
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

