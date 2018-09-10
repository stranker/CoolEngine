#pragma once
#include "GameBase.h"
#include "Triangle.h"
#include "Material.h"

#include <iostream>
using namespace std;
class Game : public GameBase
{
protected:		
	bool OnStart() override;
	bool OnStop() override;
	bool OnUpdate() override;
	int loopCount;
	Triangle* triangle;	
	Material* mat;
	float* coord;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

