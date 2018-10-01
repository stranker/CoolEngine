#pragma once
#include "GameBase.h"
#include "Triangle.h"
#include "Square.h"
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
	Square* triangle;	
	Material* mat;
	float* coord;
	float x;
public:
	Game(int _screenHeight, int _screenWidht, string _screenName);
	~Game();
};

