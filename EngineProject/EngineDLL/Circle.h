#pragma once
#include "Shape.h"
class ENGINEDLL_API Circle :
	public Shape
{
public:
	Circle(Renderer* _renderer);
	~Circle();
	void Draw() override;
	void CalculateCircleVertex();
	void OnCollision() override {};
	void OnUpdate(float deltaTime) override {};
	void SetRadius(float _radius);
private:
	float radius;
	float vertexSeparationInDegrees;
};

