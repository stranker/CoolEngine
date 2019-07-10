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
	CreateGameObjects();
	CreateRigidbodies();
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
	if (ground && mat)
	{
		ground->SetMaterial(mat);
	}
	if (turret && mat)
	{
		turret->SetMaterial(mat);
		turret->SetTexture("Nave.bmp");
		turret->SetFrameType(40, 40, 7);
		turret->SetFrame(0);
	}
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
	conta += deltaTime * 1;
	turret->Draw();
	turret->OnUpdate(deltaTime);
	player->OnUpdate(deltaTime);
	landingPlatform->OnUpdate(deltaTime);
	player->Draw();
	landingPlatform->Draw();
	ground->Draw();

	// Ground contact

	for (b2ContactEdge* ce = landingPlatform->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbody = c->GetFixtureA()->GetBody();
		if (pbody != NULL)
		{
			if (pbody->GetLinearVelocity().y < -2.0f)
			{
				pbody->SetTransform(player->GetInitialPos(), 0);
				pbody->SetLinearVelocity(b2Vec2_zero);
				player->Translate(player->GetInitialPos().x, player->GetInitialPos().y);
			}
		}
	}

	for (b2ContactEdge* ce = ground->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbody = c->GetFixtureB()->GetBody();
		void* p = pbody->GetUserData();
		if (p)
		{
			pbody->SetTransform(player->GetInitialPos(), 0);
			pbody->SetLinearVelocity(b2Vec2_zero);
			player->Translate(player->GetInitialPos().x, player->GetInitialPos().y);
		}
	}
	if (loopCount > 10000)
	{		
		return false;
	}

	return true;
}

void Game::CreateGameObjects()
{
	mat = new Material();
	const b2Vec2 gravity = b2Vec2(0, -1);
	world2D = new b2World(gravity);
	landingPlatform = new Platform(renderer);
	player = new Player(renderer);
	turret = new Turret(renderer);
	ground = new Line2D(renderer);
}

void Game::CreateRigidbodies()
{
	// Body def player
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(0, 400); //set the starting position
	myBodyDef.angle = 90; //set the starting angle
	myBodyDef.gravityScale = 0.08f;
	myBodyDef.userData = &player;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(30, 30);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 0.1f;
	b2Body* playerRigid = world2D->CreateBody(&myBodyDef);
	playerRigid->CreateFixture(&boxFixtureDef);
	player->SetRigidbody(playerRigid);

	// Body def platform
	b2BodyDef myBodyDefPlat;
	myBodyDefPlat.type = b2_staticBody; //this will be a static body
	myBodyDefPlat.position.Set(100, 100); //set the starting position
	myBodyDefPlat.angle = 0; //set the starting angle
	myBodyDefPlat.userData = &landingPlatform;
	b2PolygonShape boxShapePlat;
	boxShapePlat.SetAsBox(30, 30);
	b2FixtureDef boxFixtureDefPlat;
	boxFixtureDefPlat.shape = &boxShapePlat;
	boxFixtureDefPlat.density = 1;
	b2Body* platRigid = world2D->CreateBody(&myBodyDefPlat);
	platRigid->CreateFixture(&boxFixtureDefPlat);
	landingPlatform->SetRigidbody(platRigid);

	// Body def turret
	b2BodyDef myBodyDefTurr;
	myBodyDefTurr.type = b2_staticBody; //this will be a static body
	myBodyDefTurr.position.Set(200, 100); //set the starting position
	myBodyDefTurr.userData = &turret;
	b2PolygonShape boxShapeTurr;
	boxShapeTurr.SetAsBox(30, 30);
	b2FixtureDef boxFixtureDefTurret;
	boxFixtureDefTurret.shape = &boxShapeTurr;
	boxFixtureDefTurret.density = 1;
	b2Body* turretRigid = world2D->CreateBody(&myBodyDefTurr);
	turretRigid->CreateFixture(&boxFixtureDefTurret);
	turret->SetRigidbody(turretRigid);

	// Ground
	b2Vec2 vs[4];
	vs[0].Set(0.0f, -50);
	vs[1].Set(200.0f, -100.0f);
	vs[2].Set(300.0f, -200.0f);
	vs[3].Set(400.0f, -200.0f);
	b2BodyDef chainDef;
	chainDef.type = b2_staticBody;
	chainDef.position.Set(0, -50); //set the starting position
	chainDef.userData = &ground;
	b2ChainShape chain;
	chain.CreateChain(vs, 4);
	b2FixtureDef chainFixture;
	chainFixture.shape = &chain;
	chainFixture.density = 1;
	b2Body* groundRigid = world2D->CreateBody(&chainDef);
	groundRigid->CreateFixture(&chainFixture);
	list<b2Vec2> groundList;
	groundList.push_back(vs[0]);
	groundList.push_back(vs[1]);
	groundList.push_back(vs[2]);
	groundList.push_back(vs[3]);
	ground->SetLinesVertices(groundList);
	ground->SetRigidbody(groundRigid);
}
