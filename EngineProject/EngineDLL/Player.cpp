#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	flyingAnimation = new Animation(this);
	dieAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	flyingAnimation->CreateAnimation("Flying", 0, 2, false);
	dieAnimation->CreateAnimation("Die", 3, 6, false);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(flyingAnimation);
	animator->AddAnimation(dieAnimation);
	SetPosition(-200, 0, 5);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	
	// Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {
		animator->Play("Flying", deltaTime);
	}
	else
	{
		animator->Play("Idle", deltaTime);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x+BBWidth - 1.0f, GetPos().y + 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + BBWidth - 1.0f, (GetPos().y + BBHeight - 1.0f)))
		{
			float x = Tilemap::GetInstance()->GetTileX(GetPos().x + BBWidth);

			SetPosition(x-BBWidth, GetPos().y, GetPos().z);
		}
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {	
		if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y + 1.0f) || Tilemap::GetInstance()->NextTileIsCollider(GetPos().x + 1.0f, GetPos().y+BBHeight - 1.0f))
		{
			SetPosition(Tilemap::GetInstance()->GetTileX(GetPos().x)+BBWidth, GetPos().y, GetPos().z);
		}
	}
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_1) == GLFW_PRESS) {
		SetPosition(-200, 0, 5);
	}
}
