#include "Game.h"
#include "GLFW\glfw3.h"
#include "GLFW\glfw3native.h"
Game::Game(int _screenWidht, int _screenHeight, string _screenName) : GameBase(_screenWidht, _screenHeight, _screenName)
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
	renderer->SetNewCameraSize(1024.0f, 768.0f);
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
		landingPlatform->SetFrameType(50, 20, 4);
		landingPlatform->SetFrame(0);
	}
	if (bullet && mat)
	{
		bullet->SetMaterial(mat);
		bullet->SetTexture("Bullet.bmp");
		bullet->SetFrameType(16, 16, 1);
		bullet->SetFrame(0);
	}
	if (bullet2 && mat)
	{
		bullet2->SetMaterial(mat);
		bullet2->SetTexture("Bullet.bmp");
		bullet2->SetFrameType(16, 16, 1);
		bullet2->SetFrame(0);
	}
	if (ground && mat)
	{
		ground->SetMaterial(mat);
	}
	if (turret && mat)
	{
		turret->SetMaterial(mat);
		turret->SetTexture("Turret.bmp");
		turret->SetFrameType(32, 32, 1);
		turret->SetFrame(0);
	}
	if (turret2 && mat)
	{
		turret2->SetMaterial(mat);
		turret2->SetTexture("Turret.bmp");
		turret2->SetFrameType(32, 32, 1);
		turret2->SetFrame(0);
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
	turret2->Draw();
	turret->OnUpdate(deltaTime);
	turret2->OnUpdate(deltaTime);
	player->OnUpdate(deltaTime);
	landingPlatform->OnUpdate(deltaTime);
	player->Draw();
	landingPlatform->Draw();
	ground->Draw();
	bullet->Draw();
	bullet->OnUpdate(deltaTime);
	bullet2->Draw();
	bullet2->OnUpdate(deltaTime);

	// Spawn bullet
	if (turret->CanShot() && !win)
	{
		turret->Shot();
		bullet->GetRigidbody()->SetTransform(turret->GetRigidbody()->GetPosition() + b2Vec2(0, 60), 0);
		bullet->GetRigidbody()->SetLinearVelocity(b2Vec2_zero);
		bullet->Fired(turret->GetRigidbody()->GetPosition() + b2Vec2(0, 100), player->GetRigidbody()->GetPosition());
	}

	if (turret2->CanShot() && !win)
	{
		turret2->Shot();
		bullet2->GetRigidbody()->SetTransform(turret2->GetRigidbody()->GetPosition() + b2Vec2(0, 60), 0);
		bullet2->GetRigidbody()->SetLinearVelocity(b2Vec2_zero);
		bullet2->Fired(turret2->GetRigidbody()->GetPosition() + b2Vec2(0, 100), player->GetRigidbody()->GetPosition());
	}
	// Ground contact

	for (b2ContactEdge* ce = landingPlatform->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbodyA = c->GetFixtureA()->GetBody();
		b2Body* pbodyB = c->GetFixtureB()->GetBody();
		if (pbodyA->GetUserData() != NULL && pbodyB->GetUserData() != NULL)
		{
			void *g = pbodyA->GetUserData();
			void *b = pbodyB->GetUserData();
			if (player->GetRigidbody()->GetUserData() == pbodyB->GetUserData())
			{
				if (pbodyB->GetLinearVelocity().y < -1.0f) {
					pbodyB->SetTransform(player->GetInitialPos() + b2Vec2(-600, 0), 0);
					pbodyB->SetLinearVelocity(b2Vec2_zero);
				}
				else
				{
					win = true;
				}
			}
		}
	}

	for (b2ContactEdge* ce = ground->GetRigidbody()->GetContactList(); ce; ce = ce->next)
	{
		b2Contact* c = ce->contact;
		b2Body* pbodyA = c->GetFixtureA()->GetBody();
		b2Body* pbodyB = c->GetFixtureB()->GetBody();
		if (pbodyA->GetUserData() != NULL && pbodyB->GetUserData() != NULL)
		{
			if (player->GetRigidbody()->GetUserData() == pbodyB->GetUserData())
			{
				pbodyB->SetTransform(player->GetInitialPos() + b2Vec2(-600, 0), 0);
				pbodyB->SetLinearVelocity(b2Vec2_zero);
			}
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
	const b2Vec2 gravity = b2Vec2(0, -10);
	world2D = new b2World(gravity);
	landingPlatform = new Platform(renderer);
	player = new Player(renderer);
	turret = new Turret(renderer);
	turret2 = new Turret(renderer);
	ground = new Line2D(renderer);
	bullet = new Bullet(renderer);
	bullet2 = new Bullet(renderer);
	bullet->SetScale(0.5f, 0.5f, 0.5f);
	bullet2->SetScale(0.5f, 0.5f,0.5f);
}

void Game::CreateRigidbodies()
{
	// Ground
	ground->CreateRandomLine(LENGTH_TERRAIN, 2);
	b2BodyDef chainDef;
	chainDef.type = b2_staticBody;
	chainDef.position.Set(0, -20); //set the starting position
	chainDef.userData = &ground;
	b2ChainShape chain;
	b2Vec2 points[LENGTH_TERRAIN];
	for (int i = 0; i < LENGTH_TERRAIN; i++)
	{
		points[i].Set(ground->points[i].x, ground->points[i].y);
	}
	chain.CreateChain(points, LENGTH_TERRAIN);
	b2FixtureDef chainFixture;
	chainFixture.shape = &chain;
	b2Body* groundRigid = world2D->CreateBody(&chainDef);
	groundRigid->CreateFixture(&chainFixture);
	ground->SetRigidbody(groundRigid);

	// Body def player
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	myBodyDef.position.Set(1000, 500); //set the starting position
	myBodyDef.angle = 90; //set the starting angle
	myBodyDef.gravityScale = 1;
	myBodyDef.userData = &player;
	b2PolygonShape boxShape;
	boxShape.SetAsBox(35, 35);
	b2FixtureDef boxFixtureDef;
	boxFixtureDef.shape = &boxShape;
	boxFixtureDef.density = 0.1f;
	b2Body* playerRigid = world2D->CreateBody(&myBodyDef);
	playerRigid->CreateFixture(&boxFixtureDef);
	player->SetRigidbody(playerRigid);
	playerRigid->SetLinearVelocity(b2Vec2(100,0));

	// Body def platform
	b2BodyDef myBodyDefPlat;
	myBodyDefPlat.type = b2_staticBody; //this will be a static body
	myBodyDefPlat.position.Set(ground->platPoint.x, ground->platPoint.y); //set the starting position
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
	b2BodyDef myBodyDefTurr2;
	myBodyDefTurr.type = myBodyDefTurr2.type = b2_staticBody; //this will be a static body
	myBodyDefTurr.position.Set(ground->turretsPoint[0].x, ground->turretsPoint[0].y); //set the starting position
	myBodyDefTurr2.position.Set(ground->turretsPoint[1].x, ground->turretsPoint[1].y); //set the starting position
	myBodyDefTurr.userData = &turret;
	myBodyDefTurr2.userData = &turret2;
	b2PolygonShape boxShapeTurr;
	boxShapeTurr.SetAsBox(30, 30);
	b2FixtureDef boxFixtureDefTurret;
	boxFixtureDefTurret.shape = &boxShapeTurr;
	boxFixtureDefTurret.density = 1;
	b2Body* turretRigid = world2D->CreateBody(&myBodyDefTurr);
	b2Body* turretRigid2 = world2D->CreateBody(&myBodyDefTurr2);
	turretRigid->CreateFixture(&boxFixtureDefTurret);
	turretRigid2->CreateFixture(&boxFixtureDefTurret);
	turret->SetRigidbody(turretRigid);
	turret2->SetRigidbody(turretRigid2);

	//body def Bullet
	b2BodyDef bdb;
	b2BodyDef bdb2;
	bdb.type = bdb2.type = b2_dynamicBody; //this will be a dynamic body
	bdb.position.Set(-1000, -1000); //set the starting position
	bdb2.position.Set(-1000, -1000); //set the starting position
	bdb.gravityScale = bdb2.gravityScale = 0.2f;
	bdb.userData = &bullet;
	bdb2.userData = &bullet2;
	bdb.bullet = bdb2.bullet = true;
	b2PolygonShape boxShapeBull;
	boxShapeBull.SetAsBox(2, 2);
	b2FixtureDef boxFixtureDefBull;
	b2FixtureDef boxFixtureDefBull2;
	boxFixtureDefBull.shape = &boxShapeBull;
	boxFixtureDefBull2.shape = &boxShapeBull;
	boxFixtureDefBull.density = boxFixtureDefBull2.density = 0.01f;
	b2Body* bulletRigid = world2D->CreateBody(&bdb);
	b2Body* bulletRigid2 = world2D->CreateBody(&bdb2);
	bulletRigid->CreateFixture(&boxFixtureDefBull);
	bulletRigid2->CreateFixture(&boxFixtureDefBull2);
	bullet->SetRigidbody(bulletRigid);
	bullet2->SetRigidbody(bulletRigid2);
}
