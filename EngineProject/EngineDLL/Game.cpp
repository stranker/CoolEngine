#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
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
	tilemap = new Tilemap(renderer, screenHeight, screenWidth);
	tilemap->SetColliderTiles({6});
	player = new Player(renderer);	
	if(triangle && mat)
	triangle->SetMaterial(mat);
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("bitmap2.bmp");
		player->SetFrameType(64, 64, 8);
		player->SetFrame(0);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}	
	player->CreateCollider(1.0f, 1.0f, false, false);
	triangle->CreateCollider(1.0f,1.0f, false, false);
	CollisionManager::GetInstance()->AddToGroup("A", player);
	CollisionManager::GetInstance()->AddToGroup("B", triangle);
	triangle->SetPosition(0, -3, 0);
	return true;		
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;		
	return false;
}
bool Game::OnUpdate(float deltaTime)
{			
	renderer->CameraFollow(player->GetPos());
	CollisionManager::GetInstance()->Update();	
	tilemap->Draw();
	player->OnUpdate(deltaTime);
	player->Draw();
	triangle->Draw();	

	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}