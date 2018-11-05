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
		sprite->SetFrameType(64, 64, 4);
		sprite->SetFrame(4);
	}

	x = 0;
	sprite->CreateCollider(1, 1, false, false);
	triangle->CreateCollider(1, 1, false, false);
	CollisionManager::GetInstance()->AddToGroup("A", sprite);
	CollisionManager::GetInstance()->AddToGroup("B", triangle);
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
	//std::cout << "Loop" << loopCount << std::endl;		
	x += 0.1f;
	CollisionManager::GetInstance()->Update();
	triangle->SetPosition(5, 0,0);
	sprite->SetPosition(x, 0, 0);
	sprite->Draw();

	triangle->Draw();	

	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}
