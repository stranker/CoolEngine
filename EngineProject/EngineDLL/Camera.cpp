#include "Camera.h"
#include "GLFW\glfw3.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

Camera::Camera(Renderer* _renderer) : Entity(_renderer)
{
	renderer->SetCameraType(Renderer::PERSPECTIVE);
	forward[0] = forward[1] = 0;
	forward[2] = 1;
	up[0] = up[2] = 0;
	up[1] = 1;
}

void Camera::OnUpdate(float deltaTime)
{
	//Move forward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_W) == GLFW_PRESS)
	{
		Walk(speed * deltaTime);
	}
	// Move backward
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_S) == GLFW_PRESS)
	{		
		Walk(-speed * deltaTime);
	}
	// Move Left
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_A) == GLFW_PRESS)
	{
		Strafe(speed * deltaTime);
	}	
	// Move Right
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_D) == GLFW_PRESS)
	{
		Strafe(-speed * deltaTime);
	}
	// Pitch 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_Q) == GLFW_PRESS)
	{
		Pitch(-speed * deltaTime);
	}
	// Pitch 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_E) == GLFW_PRESS)
	{
		Pitch(speed * deltaTime);
	}
	// Yaw 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_Z) == GLFW_PRESS)
	{
		Yaw(-speed * deltaTime);
	}
	// Yaw 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_X) == GLFW_PRESS)
	{
		Yaw(speed * deltaTime);
	}
	// Roll 1
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_F) == GLFW_PRESS)
	{
		Roll(-speed * deltaTime);
	}
	// Roll 2
	if (glfwGetKey((GLFWwindow*)renderer->window->GetWindowPrt(), GLFW_KEY_G) == GLFW_PRESS)
	{
		Roll(speed * deltaTime);

	}
}
Camera::~Camera()
{
}

void Camera::Walk(float velocity)
{	
	MoveIn(0, velocity);
}
void Camera::Strafe(float velocity)
{
	MoveIn(velocity, 0);
}
void Camera::Pitch(float velocity)
{		
	SetRotateY(velocity);
}
void Camera::Yaw(float velocity)
{
	SetRotateZ(velocity);
}
void Camera::Roll(float velocity)
{
	SetRotateX(velocity);
}
void Camera::MoveIn(float x, float z)
{
	pos[0] += x;
	pos[1] += 0;
	pos[2] += z;
	translate = glm::translate(glm::mat4(1.0f), pos);
	UpdateModelMatrix();
}
void Camera::SetRotateX(float x)
{	
	rot[0] += x;
	glm::vec3 axis;
	axis[0] = x;
	axis[1] = axis[2] = 0;
	rotateX = glm::rotate(glm::mat4(1.0f), rot[0], axis);
	UpdateModelMatrix();
}
void Camera::SetRotateY(float y)
{	
	rot[1] += y;
	glm::vec3 axis;
	axis[1] = y;
	axis[0] = axis[2] = 0;
	rotateY = glm::rotate(glm::mat4(1.0f), rot[1], axis);
	UpdateModelMatrix();
}
void Camera::SetRotateZ(float z)
{	
	rot[2] += z;
	glm::vec3 axis;
	axis[2] = z;
	axis[0] = axis[1] = 0;	
	rotateZ = glm::rotate(glm::mat4(1.0f), rot[2], axis);
	UpdateModelMatrix();
}
void Camera::UpdateModelMatrix()
{
	glm::mat4 rotationMatrix = rotateX * rotateY * rotateZ;
	glm::mat4 model = translate * rotationMatrix;

	glm::vec4 finalPos;
	finalPos[0] = finalPos[1] = finalPos[2] = 0; finalPos[3] = 1;
	finalPos = model * finalPos;			
	glm::vec3 targetForward = forward + glm::vec3(finalPos);

	glm::vec4 finalRotation;
	finalRotation[0] = finalRotation[1] = finalRotation[2] = 0; finalRotation[3] = 1;
	finalRotation = rotationMatrix * finalRotation;
	glm::vec3 targetUp = up + glm::vec3(finalRotation);
	
	renderer->SetViewMatrix(finalPos, targetForward, targetUp);
}

