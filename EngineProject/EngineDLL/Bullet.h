#pragma once
#include "Sprite.h"

class ENGINEDLL_API Bullet : public Sprite
{
public:
	Bullet(Renderer* rend);
	~Bullet();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	b2Body* GetRigidbody();
	b2Vec2 GetInitialPos();
	void Fired(b2Vec2 initPos, b2Vec2 playerPos);
private:
	b2Body* rigidBody;
	b2Vec2 direction = b2Vec2_zero;
	b2Vec2 initialPos;
};

