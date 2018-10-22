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
	triangle = new Square(renderer);
	circle = new Circle(renderer);
	sprite = new Sprite(renderer);
	if(triangle && mat)
	triangle->SetMaterial(mat);
	if (circle && mat)
		circle->SetMaterial(mat);
	if (sprite && mat)
	{
		sprite->SetMaterial(mat);
		sprite->SetTexture("bitmap2.bmp");
	}
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
	sprite->Draw();		
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}
