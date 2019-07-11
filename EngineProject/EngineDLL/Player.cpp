#include "Player.h"
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
	SetName("Player");
	fuel = maxFuel;
}


Player::~Player()
{
}

void Player::OnUpdate(float deltaTime)
{
	direction = b2Vec2(cos(((angleRotation * RADTODEG) + 90) * DEGTORAD), sin(((angleRotation * RADTODEG) + 90) * DEGTORAD));
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_F) == GLFW_PRESS)
	{
		fuel = maxFuel;
	}
	
	// Move UP
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS && fuel>0) {
		animator->Play("Flying", deltaTime);
		rigidBody->ApplyForceToCenter(50000 * direction, true);
		fuel -= deltaTime * 10;
		cout << "Remaining Fuel: " << (int)fuel << endl;
	}
	else
	{
		animator->Play("Idle", deltaTime);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		angleRotation -= deltaTime * 1;

	}
	// Strafe left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_LEFT) == GLFW_PRESS) {	
		angleRotation += deltaTime * 1;

	}
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_1) == GLFW_PRESS) {
		SetPosition(-200, 0, 5);
	}
	if (rigidBody)
		SetPosition(rigidBody->GetPosition().x, rigidBody->GetPosition().y,0);
	SetRotate(0,0,angleRotation);
}

void Player::SetRigidbody(b2Body * body)
{
	rigidBody = body;
	initialPos = rigidBody->GetPosition();
}

b2Body * Player::GetRigidbody()
{
	return rigidBody;
}

b2Vec2 Player::GetInitialPos()
{
	return initialPos;
}

void Player::AnimationPlay(const char * animName, float deltaTime)
{
	animator->Play(animName, deltaTime);
}

bool Player::IsAlive()
{
	return alive;
}

void Player::SetAlive(bool val)
{
	alive = val;
}
