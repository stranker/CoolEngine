#include "Turret.h"
#include "Turret.h"
#include "Turret.h"

Turret::Turret(Renderer * rend) : Sprite(rend)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	animator->AddAnimation(idleAnimation);
	SetName("Turret");
}

Turret::~Turret()
{
}

void Turret::OnUpdate(float deltaTime)
{
	if (!can_shot)
	{
		timer += deltaTime;
		if (timer > 5)
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

float Turret::GetAngleTo(b2Vec2 pos)
{
	b2Vec2 vec = pos - rigidBody->GetPosition();
	return acos(vec.x);
}
