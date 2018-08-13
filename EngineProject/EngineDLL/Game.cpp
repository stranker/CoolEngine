#include "Game.h"



Game::Game()
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
