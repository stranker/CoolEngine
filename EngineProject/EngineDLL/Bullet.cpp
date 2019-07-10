#include "Bullet.h"

Bullet::Bullet(Renderer* rend) : Sprite(rend)
{
}


Bullet::~Bullet()
{
}

void Bullet::OnUpdate(float deltaTime)
{
	if (rigidBody)
	{
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y, 0);
	}
}

void Bullet::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

b2Body * Bullet::GetRigidbody()
{
	return rigidBody;
}

b2Vec2 Bullet::GetInitialPos()
{
	return initialPos;
}

void Bullet::Fired(b2Vec2 initPos, b2Vec2 playerPos)
{
	initialPos = initPos;
	b2Vec2 vec = playerPos - initialPos;
	float norm = sqrt(vec.x * vec.x + vec.y * vec.y);
	b2Vec2 direction = b2Vec2(vec.x / norm, vec.y / norm);
	rigidBody->SetLinearVelocity(100 * direction);
}
