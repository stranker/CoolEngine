#include "Turret.h"

Turret::Turret(Renderer * rend) : Sprite(rend)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	animator->AddAnimation(idleAnimation);
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
}

void Turret::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}
