#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer) : Sprite(_renderer)
{
	animator = new Animation(this);
	animator->CreateAnimation(0, 10);
	SetPosition(0, 0, 5);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	animator->OnUpdate(deltaTime);
	// Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {			
		if (Tilemap::GetInstance()->GetTile(GetPos().x, GetPos().y + BBHeight/2 + speed*deltaTime))
		{
			MoveIn(0, -speed*deltaTime, 0);
		}
		else
		{
			MoveIn(0, speed * deltaTime, 0);
		}
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_DOWN) == GLFW_PRESS) {
		MoveIn(0, -speed*deltaTime, 0);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		MoveIn(speed*deltaTime,0, 0);
	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {
		MoveIn(-speed*deltaTime, 0, 0);
	}
}
