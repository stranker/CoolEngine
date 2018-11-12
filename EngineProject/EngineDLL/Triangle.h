#pragma once
#include "Shape.h"
class ENGINEDLL_API Triangle : public Shape
{
public:
	Triangle(Renderer* _renderer);
	~Triangle();
	void Draw() override;
	void OnCollision() override {};
	void OnUpdate(float deltaTime) override {};
};