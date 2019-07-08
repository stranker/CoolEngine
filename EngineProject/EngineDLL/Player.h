#pragma once
#include "AnimationPlayer.h"
#include "Exports.h"


class ENGINEDLL_API Player : public Sprite
{
public:
	Player(Renderer* _renderer);
	~Player();
	void OnUpdate(float deltaTime) override;
	float speed = 200;
	void SetRigidbody(b2Body* body);
	const b2BodyDef GetRigidbodyDef();
	const b2FixtureDef GetBodyFixture();
private:
	Animation * idleAnimation;
	Animation * flyingAnimation;
	Animation * dieAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	b2BodyDef bodyDef;
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;
	float angleRotation;
};

