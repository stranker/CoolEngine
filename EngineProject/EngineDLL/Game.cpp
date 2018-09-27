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
<<<<<<< HEAD
	x = 0;
	return true;	
=======
	return true;
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate()
{
	loopCount++;	
<<<<<<< HEAD
	std::cout << "Loop" << loopCount << std::endl;		
	x += 0.1f;
	triangle->SetRotateY(x);
=======
	std::cout << "Loop" << loopCount << std::endl;
>>>>>>> d7e329e810e22936c4fce1969a38f7f0758fde97
	triangle->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}
