#pragma once
#include "Animation.h"
#include "AnimationPlayer.h"
#include "Exports.h"
#include "World.h"

class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer, World* world);
	~Player();
	void OnUpdate(float deltaTime) override;
	float speed = 200;
	b2BodyDef bodyDef;
	b2Body* body;
private:
	Animation * idleAnimation;
	Animation * flapAnimation;
	Animation * flyingAnimation;
	Animation * dieAnimation;
	AnimationPlayer * animator;
};

