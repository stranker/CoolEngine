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
private:
	float radius;
	float vertexSeparationInDegrees;
};

