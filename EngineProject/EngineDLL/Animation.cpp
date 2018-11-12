#include "Animation.h"


Animation::Animation(Sprite* _sprite) :
	sprite(_sprite)
{
	speed = 1.0f/8.0f;
	timer = 0;
}
void Animation::CreateAnimation(float start, float end)
{
	from = start;
	to = end;
	currentKey = start;	
	if(sprite)
	sprite->SetFrame(currentKey);
}

void Animation::RunAnimation()
{
	if (sprite)
	{
		if (currentKey <= to)
		{
			sprite->SetFrame(currentKey);
			currentKey++;
		}
		else
		{
			currentKey = from;
		}
	}
}
void Animation::OnUpdate(float deltaTime)
{

	if (timer >= speed)
	{		
		RunAnimation();
		timer = 0;
	}
	else
	{
		timer += deltaTime;
	}
}
