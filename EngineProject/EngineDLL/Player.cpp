#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new Animation(this);
	animator->CreateAnimation(0, 10);
	SetPosition(-100, 0, 5);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	animator->OnUpdate(deltaTime);
	// Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {			
			MoveIn(0, speed * deltaTime, 0);
		if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x, GetPos().y))
		{								
			SetPosition(GetPos().x, Tilemap::GetInstance()->GetLastTileY() -194
				, GetPos().z);			 						
		}
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_DOWN) == GLFW_PRESS) {
			MoveIn(0, -speed * deltaTime, 0);				
		if (Tilemap::GetInstance()->NextTileIsCollider(GetPos().x, GetPos().y))
		{
			SetPosition(GetPos().x, Tilemap::GetInstance()->GetLastTileY()+BBHeight, GetPos().z);
		}
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		MoveIn(speed*deltaTime, 0, 0);
		if (
			Tilemap::GetInstance()->NextTileIsCollider(GetPos().x, GetPos().y))
		{
			SetPosition(Tilemap::GetInstance()->GetLastTileX()-BBWidth, GetPos().y, GetPos().z);
		}
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {
			MoveIn(-speed * deltaTime, 0, 0);			
		if (!Tilemap::GetInstance()->NextTileIsCollider(GetPos().x, GetPos().y))
		{
			SetPosition(Tilemap::GetInstance()->GetLastTileX(), GetPos().y, GetPos().z);
		}
	}
}
