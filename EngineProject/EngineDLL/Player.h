#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"
#include "Sprite.h"

class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer);
	~Player();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	b2Body* GetRigidbody();
	b2Vec2 GetInitialPos();
	void AnimationPlay(const char* animName, float deltaTime);
	bool IsAlive();
	void SetAlive(bool val);
private:
	Animation * idleAnimation;
	Animation * flyingAnimation;
	Animation * dieAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	float angleRotation = 0;
	b2Vec2 direction = b2Vec2_zero;
	b2Vec2 initialPos;
	bool alive = true;
	float fuel = 0;
	float maxFuel = 100;
};

