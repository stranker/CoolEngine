#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"
#include "Sprite.h"

class ENGINEDLL_API Turret : public Sprite
{
public:
	Turret(Renderer* rend);
	~Turret();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	b2Body* GetRigidbody();
	bool CanShot();
	void Shot();
private:
	Animation * idleAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	float angleRotation = 0;
	b2Vec2 direction = b2Vec2_zero;
	bool can_shot = true;
	float timer = 0;
};

