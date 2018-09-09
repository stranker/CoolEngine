#include "Game.h"



Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;
	coord = new float[
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		0.0f,  1.0f, 0.0f
	];
}


Game::~Game()
{
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;
	triangle = new Triangle(renderer);
	triangle->SetVertices(coord,9);
	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate()
{
	loopCount++;	
	std::cout << "Loop" << loopCount << std::endl;
	if (loopCount > 10000)
	{		
		triangle->Draw();
		return false;
	}

	return true;
}
