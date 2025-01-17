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
	SetName("Platform");
}


Platform::~Platform()
{
}

void Platform::OnUpdate(float deltaTime)
{
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x,rigidBody->GetPosition().y, 0);
	}
}

void Platform::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

b2Body * Platform::GetRigidbody()
{
	return rigidBody;
}

void Platform::AnimationPlay(const char* animName, float deltaTime)
{
	animator->Play(animName,deltaTime);
}
