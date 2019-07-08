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
	bodyDef.type = b2_dynamicBody;
	bodyDef.angle = 0;
	bodyDef.gravityScale = 0.1f;
	boxShape.SetAsBox(1, 1);
	angleRotation = 0.1;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 1;
}


Player::~Player()
{
}

void Player::OnUpdate(float deltaTime)
{
	// Move UP
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(),GLFW_KEY_UP) == GLFW_PRESS) {
		animator->Play("Flying", deltaTime);
		rigidBody->SetLinearVelocity(deltaTime * b2Vec2(0,10));
	}
	else
	{
		animator->Play("Idle", deltaTime);
	}
	// Strafe right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
		//rigidBody->SetAngularVelocity(10 * deltaTime);
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
		Translate(rigidBody->GetPosition().x, rigidBody->GetPosition().y);
	SetRotate(0,0,angleRotation);
}

void Player::SetRigidbody(b2Body * body)
{
	rigidBody = body;
}

const b2BodyDef Player::GetRigidbodyDef()
{
	return bodyDef;
}

const b2FixtureDef Player::GetBodyFixture()
{
	return fixtureDef;
}
