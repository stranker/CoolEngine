#include "Game.h"

Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;	
}


Game::~Game()
{
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;	
	mat = new Material();
	triangle = new Triangle(renderer);
	if(triangle && mat)
	triangle->SetMaterial(mat);
	x = 0;
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
	x += 0.1f;
	triangle->SetScale(x, x, x);
	triangle->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}
