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
	//ground = new Line2D(renderer);

	// Body def player
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(0, 0); //set the starting position
	myBodyDef.angle = 90; //set the starting angle
	myBodyDef.gravityScale = 0.05f;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 1;
	b2Body* playerRigid = world2D->CreateBody(&myBodyDef);
	playerRigid->CreateFixture(&boxFixtureDef);
	player->SetRigidbody(playerRigid);

	// Body def platform
	b2BodyDef myBodyDefPlat;
	myBodyDefPlat.type = b2_staticBody; //this will be a static body
	myBodyDefPlat.position.Set(100, 100); //set the starting position
	myBodyDefPlat.angle = 0; //set the starting angle
	b2PolygonShape boxShapePlat;
	boxShapePlat.SetAsBox(40, 40);
	b2FixtureDef boxFixtureDefPlat;
	boxFixtureDefPlat.shape = &boxShapePlat;
	boxFixtureDefPlat.density = 1;
	b2Body* platRigid = world2D->CreateBody(&myBodyDefPlat);
	platRigid->CreateFixture(&boxFixtureDefPlat);
	landingPlatform->SetRigidbody(platRigid);

	// Ground
	b2Vec2 vs[4];
	vs[0].Set(1.7f, 0.0f);
	vs[1].Set(1.0f, 0.25f);
	vs[2].Set(0.0f, 0.0f);
	vs[3].Set(-1.7f, 0.4f);	list<b2Vec2> groundList;
	groundList.push_back(vs[0]);
	groundList.push_back(vs[1]);
	groundList.push_back(vs[2]);
	groundList.push_back(vs[3]);
	b2ChainShape chain;
	chain.CreateChain(vs, 4);
	
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
	if (ground)
	{
		ground->SetMaterial(mat);
	}
	if (tilemap && mat)
	{
		tilemap->SetMaterial(mat);
		tilemap->SetFrameType(32, 32, 6);
		tilemap->SetTexture("tilemap.bmp");
	}
	//CollisionManager::GetInstance()->AddToGroup("A", player);
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
	//CollisionManager::GetInstance()->Update();
	conta += deltaTime * 1;
	tilemap->Draw();
	player->OnUpdate(deltaTime);
	landingPlatform->OnUpdate(deltaTime);
	player->Draw();
	landingPlatform->Draw();
	//ground->Draw();
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}