#include "Player.h"

Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new Animation(this);
	animator->CreateAnimation(0, 4);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	animator->OnUpdate(deltaTime);
}
