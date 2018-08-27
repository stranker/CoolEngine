#include "Game.h"



Game::Game(int _screenWidht, int _screenHeight, string _screenName) : GameBase(_screenWidht, _screenHeight,_screenName) // constructor de la clase padre
{
	loopCount = 0;
}


Game::~Game()
{
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;
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
	if (loopCount > 100)
		return false;

	return true;
}
