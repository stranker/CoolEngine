#include "Platform.h"

Platform::Platform(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	landingAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	landingAnimation->CreateAnimation("Landing", 0, 2, false);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(landingAnimation);
	SetPosition(-200, 100, 5);
	bodyDef.type = b2_staticBody;
	bodyDef.angle = 0;
	boxShape.SetAsBox(1, 1);
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1;
}


Platform::~Platform()
{
}

void Platform::OnUpdate(float deltaTime)
{
}

void Platform::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

const b2BodyDef Platform::GetRigidbodyDef()
{
	return bodyDef;
}

const b2FixtureDef Platform::GetBodyFixture()
{
	return fixtureDef;
}
