#include "Renderer.h"
#include "Entity.h"
#include "Exports.h"
#include "Window.h"
#include <glm\glm.hpp>
#include <glm\matrix.hpp>
#include <iostream>
using namespace std;
class ENGINEDLL_API Camera : public Entity
{
private:
	float speed = 50.0f;
	glm::vec3 forward;
	glm::vec3 up;
public:
	Camera(Renderer* _renderer);
	~Camera();
	void OnUpdate(float deltaTime) override;
	virtual void OnCollision() override {};
	virtual void Draw() override {};
	void Walk(float velocity);
	void Strafe(float velocity);
	void Pitch(float velocity);
	void Yaw(float velocity);
	void Roll(float velocity);
	void MoveIn(float x, float y);
	void SetRotateX(float x);
	void SetRotateY(float y);
	void SetRotateZ(float z);
	void UpdateModelMatrix();
};

