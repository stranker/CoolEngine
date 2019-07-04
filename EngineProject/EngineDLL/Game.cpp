#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
Game::Game(int _screenWidht, int _screenHeight, string _screenName): GameBase(_screenWidht, _screenHeight, _screenName)
{	
	loopCount = 0;	
}


Game::~Game()
{
	delete world2D;
}

bool Game::OnStart()
{
	cout << "Game::OnStart()" << endl;
	mat = new Material();
	square = new Square(renderer);
	tilemap = new Tilemap(renderer, screenHeight, screenWidth);
	tilemap->SetColliderTiles({0});
	const b2Vec2 gravity = b2Vec2(0, -4);
	world2D = new b2World(gravity);
	player = new Player(renderer);

	b2Body* rigid = world2D->CreateBody(&player->GetRigidbodyDef());
	rigid->CreateFixture(&player->GetBodyFixture());
	player->SetRigidbody(rigid);
	
	if(square && mat)
	square->SetMaterial(mat);
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("Nave.bmp");
		player->SetFrameType(40, 40, 7);
		player->SetFrame(0);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}	
	player->CreateCollider(32.0f, 32.0f, false, false);
	square->CreateCollider(64.0f,64.0f, false, false);
	CollisionManager::GetInstance()->AddToGroup("A", player);
	CollisionManager::GetInstance()->AddToGroup("B", square);
	square->SetPosition(-500, -400, 5);	
	return true;
}

bool Game::OnStop()
{
	cout << "Game::OnStop()" << endl;
	return false;
}
bool Game::OnUpdate(float deltaTime)
{	
	world2D->Step(1 / 20.0, 8, 3);
	renderer->CameraFollow(player->GetPos());
	CollisionManager::GetInstance()->Update();
	conta += deltaTime * 1;
	tilemap->Draw();
	player->OnUpdate(deltaTime);
	player->Draw();
	square->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}