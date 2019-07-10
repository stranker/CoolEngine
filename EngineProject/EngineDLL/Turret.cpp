#include "Turret.h"
#include "Turret.h"
#include "Turret.h"

Turret::Turret(Renderer * rend) : Sprite(rend)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	animator->AddAnimation(idleAnimation);
	name = "Turret";
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{
	if (!can_shot)
	{
		timer += deltaTime;
		if (timer > 3)
		{
			can_shot = true;
			timer = 0;
		}
	}
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
}

void Turret::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

b2Body * Turret::GetRigidbody()
{
	return rigidBody;
}

bool Turret::CanShot()
{
	return can_shot;
}

void Turret::Shot()
{
	can_shot = false;
}
