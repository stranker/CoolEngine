#pragma once
#include "Exports.h"
#include "Sprite.h"	
class ENGINEDLL_API Animation
{
public:
	Animation(Sprite* _sprite);
	~Animation();
	void CreateAnimation(float start, float end);
	void RunAnimation();
	void OnUpdate(float deltaTime);
private:
	float from;
	float to;
	float currentKey;
	float speed;
	float timer;
	Sprite* sprite;
};

