#include "Player.h"
#include "GLFW\glfw3.h"
#include "Tilemap.h"
Player::Player(Renderer* _renderer, World* _world) : Sprite(_renderer)
{
	animator = new AnimationPlayer();
	idleAnimation = new Animation(this);
	flapAnimation = new Animation(this);
	flyingAnimation = new Animation(this);
	dieAnimation = new Animation(this);
	idleAnimation->CreateAnimation("Idle", 0, 0, true);
	flapAnimation->CreateAnimation("Flaping", 0, 2, false);
	flyingAnimation->CreateAnimation("Flying", 2, 2, true);
	dieAnimation->CreateAnimation("Die", 3, 6, false);
	animator->AddAnimation(idleAnimation);
	animator->AddAnimation(flapAnimation);
	animator->AddAnimation(flyingAnimation);
	animator->AddAnimation(dieAnimation);
	SetPosition(-200, 0, 5);
	bodyDef.type = b2_dynamicBody;
	bodyDef.angle = 0;
	body = _world->myWorld->CreateBody(&bodyDef);
}



Player::~Player()
{
}
void Player::OnUpdate(float deltaTime)
{
	// Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {
		body->SetLinearVelocity(b2Vec2(0, 200));
		animator->Play("Flaping", deltaTime);
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
