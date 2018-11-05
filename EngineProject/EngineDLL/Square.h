#pragma once
#include "Shape.h"
class ENGINEDLL_API Square :
	public Shape
{
public:
	Square(Renderer* _renderer);
	~Square();
	void Draw() override;
	void OnCollision() override {};
};

