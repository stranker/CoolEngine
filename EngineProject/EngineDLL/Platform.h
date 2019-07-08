#pragma once
#include "Exports.h"
#include "AnimationPlayer.h"

class ENGINEDLL_API Platform :
	public Sprite
{
public:
	Platform(Renderer* _renderer);
	~Platform();
	void OnUpdate(float deltaTime) override;
	void SetRigidbody(b2Body* body);
	const b2BodyDef GetRigidbodyDef();
	const b2FixtureDef GetBodyFixture();
private:
	Animation* idleAnimation;
	Animation* landingAnimation;
	AnimationPlayer * animator;
	b2Body* rigidBody;
	b2BodyDef bodyDef;
	b2PolygonShape boxShape;
	b2FixtureDef fixtureDef;
};

