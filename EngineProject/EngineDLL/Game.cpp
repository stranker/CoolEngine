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
	tilemap = new Tilemap(renderer, screenHeight, screenWidth);
	tilemap->SetColliderTiles({0});
	const b2Vec2 gravity = b2Vec2(0, -1);
	world2D = new b2World(gravity);
	landingPlatform = new Platform(renderer);
	player = new Player(renderer);

	b2Body* playerRigid = world2D->CreateBody(&player->GetRigidbodyDef());
	playerRigid->CreateFixture(&player->GetBodyFixture());
	player->SetRigidbody(playerRigid);

	//b2Body* platRigid = world2D->CreateBody(&landingPlatform->GetRigidbodyDef());
	//platRigid->CreateFixture(&landingPlatform->GetBodyFixture());
	//landingPlatform->SetRigidbody(platRigid);
	
	if (player && mat)
	{
		player->SetMaterial(mat);
		player->SetTexture("Nave.bmp");
		player->SetFrameType(40, 40, 7);
		player->SetFrame(0);
	}
	if (landingPlatform && mat)
	{
		landingPlatform->SetMaterial(mat);
		landingPlatform->SetTexture("Platform.bmp");
		landingPlatform->SetFrameType(50,20, 4);
		landingPlatform->SetFrame(0);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}
	CollisionManager::GetInstance()->AddToGroup("A", player);
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
	landingPlatform->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}