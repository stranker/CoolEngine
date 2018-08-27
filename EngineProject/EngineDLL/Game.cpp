#include "Game.h"



Game::Game(int _screenHeight, int _screenWidht, string _screenName) : GameBase(_screenHeight,_screenWidht,_screenName) // constructor de la clase padre
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
